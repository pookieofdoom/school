#include "tinyFS.h"


int createFile(superblock *sb, char * name_block) {
  inode in;
  fileextent fe;
  int in_loc, f_loc;
  unsigned char buf[BLOCKSIZE];
  time_t cur_time;

  memset(buf, 0, BLOCKSIZE);

  //Find Space for New INode
  in_loc = nextFree(sb->free_blocks, sb->num_blocks);
  if (in_loc < 0)
    return INSUFFICIENT_SPACE;

  if(readBlock(disk, 1, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf+2, sizeof(inode));
  if(in.num_files == FOLDER_SIZE)
    return FOLDER_FULL;
  memcpy(in.entries[in.num_files].name, name_block, 8);
  in.entries[in.num_files].in_addr = in_loc;
  in.num_files += 1;
  buf[0] = INODE_TYPE;
  memcpy(buf+2, &in, sizeof(inode));
  if(writeBlock(disk, 1, buf) < 0)
    return WRITE_BLOCK_FAILED;

  //Reserve INode Space;
  reserve(sb->free_blocks, in_loc);

  //Populate INode
  f_loc = nextFree(sb->free_blocks, sb->num_blocks);
  if (f_loc < 0)
    return INSUFFICIENT_SPACE;
  in.data_address = f_loc;
  memcpy(in.name, name_block, 8);
  cur_time = time(NULL);
  in.finfo.creation = cur_time;
  in.finfo.access = cur_time;
  in.finfo.modification = cur_time;
  in.readonly = 0;

  //Write INode
  if (readBlock(disk, in_loc, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(buf + 2, &in, sizeof(inode));
  buf[0] = INODE_TYPE;
  if (writeBlock(disk, in_loc, buf) < 0)
    return WRITE_BLOCK_FAILED;

  //Reserve File Extent Space;
  reserve(sb->free_blocks, f_loc);

  //Populate File Extent Node
  if (readBlock(disk, f_loc, buf) < 0)
    return READ_BLOCK_FAILED;
  fe.nxtBlock = in_loc;
  fe.length = 1;
  memcpy(buf + 2, &fe, sizeof(fileextent));
  buf[0] = FILE_EXTENT_TYPE;
  if (writeBlock(disk, f_loc, buf) < 0)
    return WRITE_BLOCK_FAILED;

  //Save Changes to SuperBlock free vector
  buf[0] = SUPERBLOCK_TYPE;
  memcpy(buf+2, sb, sizeof(superblock));
  if(writeBlock(disk, 0, buf) < 0)
    return WRITE_BLOCK_FAILED;

  return makeTableEntry(in_loc);
}

int tfs_mkfs(char *filename, int nBytes)
{
  unsigned char ind;
  unsigned int num_blocks;
  unsigned char buf[BLOCKSIZE];
  superblock * sb;
  inode in;
  memset(buf, 0, BLOCKSIZE);

  disk = openDisk(filename, nBytes);
  if (disk <= 0)
    return OPEN_DISK_FAILED;

  //Make New File System
  if (nBytes > 0) {
    num_blocks = nBytes / BLOCKSIZE;
    buf[0] = SUPERBLOCK_TYPE;
    buf[1] = MAGIC_NUM;
    sb = (superblock *)calloc(1, sizeof(superblock));
    sb->num_blocks = num_blocks;
    reserve(sb->free_blocks, 0);
    reserve(sb->free_blocks, 1);
    sb->root_inode_addr = 1;
    memcpy(buf + 2, sb, sizeof(superblock));
    if (writeBlock(disk, 0, buf) < 0)
      return WRITE_BLOCK_FAILED;

    memset(&in, 0, sizeof(inode));
    buf[0] = INODE_TYPE;
    memcpy(in.name,"\\",1);
    in.num_files = 0;
    memcpy(buf + 2, &in, sizeof(inode));
    if (writeBlock(disk, 1, buf) < 0)
      return WRITE_BLOCK_FAILED;

    for(ind = 2; ind < num_blocks; ind++) {
      buf[0] = FREE_TYPE;
      buf[1] = MAGIC_NUM;
      buf[3] = ind == 0 ? (unsigned char)num_blocks : 0;
      if (writeBlock(disk, ind, buf) < 0)
        return WRITE_BLOCK_FAILED;
    }
    closeDisk(disk);
    disk = -1;
    return 0;
  }
  else {
    closeDisk(disk);
    disk = -1;
    return NEGATIVE_FS_SIZE;
  }
}

int tfs_mount(char *filename)
{
  unsigned char block_type, magic_num;
  unsigned char buf[BLOCKSIZE];

  memset(buf, 0, BLOCKSIZE);

  clearTable();
  disk = openDisk(filename, 0);
  if (disk < 0)
    return OPEN_DISK_FAILED;

  if(readBlock(disk, 0, buf) < 0)
      return READ_BLOCK_FAILED;
  block_type = buf[0];
  magic_num = buf[1];
  if(block_type != SUPERBLOCK_TYPE || magic_num != MAGIC_NUM)
    return INVALID_SUPERBLOCK;
  return disk;
}

int tfs_unmount(void)
{
  if (disk > 0) {
    clearTable();
    closeDisk(disk);
    return 0;
  }
  else {
    return -1;
  }
}

fileDescriptor tfs_openFile(char *name)
{
  superblock *sb;
  unsigned char buf[BLOCKSIZE];
  unsigned int ind;
  char name_block[8];
  fileDescriptor FD;
  inode in;

  if (disk <= 0)
    return OPEN_DISK_FAILED;

  memset(buf, 0, BLOCKSIZE);
  memset(name_block, 0, 8);

  if (strlen(name) > 8)
    return NAME_TOO_LONG;

  if (strncmp(name, "\\", 1) == 0 && strlen(name) == 1)
    return INVALID_NAME;

  memcpy(name_block, name, strlen(name));

  if (readBlock(disk, 0, buf) < 0)
    return READ_BLOCK_FAILED;
  sb = (superblock *)calloc(1, sizeof(superblock));
  memcpy(sb, buf+2, sizeof(superblock));

  if (readBlock(disk, 1, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf + 2, sizeof(inode));

  for(ind = 0; ind < in.num_files; ind++) {
    if(strncmp(name_block, in.entries[ind].name, 8) == 0) {
      FD = getFileDescriptor(ind);
      if (FD >= 0) {
        return FD;
      }
      return makeTableEntry(in.entries[ind].in_addr);
    }
  }

  return createFile(sb, name_block);
}

int tfs_closeFile(fileDescriptor FD)
{
  return removeTableEntry(FD);
}


int tfs_writeFile(fileDescriptor FD, char *buffer, int size)
{
  unsigned char buf[BLOCKSIZE], cur_file;
  superblock sb;
  fileextent fe;
  inode in;
  int blocks;
  time_t cur_time;

  if (disk <= 0)
    return OPEN_DISK_FAILED;

  if(isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;

  if(readBlock(disk , 0, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&sb, buf + 2, sizeof(superblock));

  blocks = size / (DATA_SIZE);
  blocks += size % (DATA_SIZE) > 0 ? 1 : 0;

  if(readBlock(disk, getInodeAddress(FD), buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf+2, sizeof(inode));

  if(in.readonly)
    return FILE_IS_READONLY;

  setFilePointer(FD, 0);


  cur_file = in.data_address;

  if(readBlock(disk, cur_file, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&fe, buf + 2, sizeof(fileextent));

  //Delete all blocks of file
  while(!fe.length) {
    release(sb.free_blocks, cur_file);
    buf[0] = FREE_TYPE;
    if(writeBlock(disk, cur_file, buf) < 0)
      return WRITE_BLOCK_FAILED;
    cur_file = fe.nxtBlock;
    if(readBlock(disk, cur_file, buf) < 0)
      return READ_BLOCK_FAILED;
    memcpy(&fe, buf + 2, sizeof(fileextent));
  }

  if(numFree(sb.free_blocks, sb.num_blocks) < blocks - 1)
    return INSUFFICIENT_SPACE;

  in.data_address = cur_file;

  while(--blocks) {

    buf[0] = FILE_EXTENT_TYPE;
    fe.length = 0;
    memcpy(fe.data, buffer, DATA_SIZE);
    fe.nxtBlock = nextFree(sb.free_blocks, sb.num_blocks);
    reserve(sb.free_blocks, fe.nxtBlock);

    memcpy(buf + 2, &fe, sizeof(fileextent));
    writeBlock(disk, cur_file, buf);

    size -= DATA_SIZE;
    buffer += DATA_SIZE;
    cur_file = fe.nxtBlock;
  }

  buf[0] = FILE_EXTENT_TYPE;
  fe.nxtBlock = getInodeAddress(FD);
  fe.length = size + 1;
  memcpy(fe.data, buffer, size);
  memcpy(buf + 2, &fe, sizeof(fileextent));
  writeBlock(disk, cur_file, buf);

  buf[0] = SUPERBLOCK_TYPE;
  memcpy(buf + 2, &sb, sizeof(superblock));
  if(writeBlock(disk, 0, buf) < 0)
    return WRITE_BLOCK_FAILED;

  cur_time = time(NULL);
  in.finfo.modification = cur_time;
  in.finfo.access = cur_time;
  memcpy(buf + 2, &in, sizeof(inode));
  buf[0] = INODE_TYPE;
  if(writeBlock(disk, getInodeAddress(FD), buf) < 0)
    return WRITE_BLOCK_FAILED;

  return 0;
}


int tfs_deleteFile(fileDescriptor FD)
{
  unsigned char buf[BLOCKSIZE], cur_file, nxt_file, len, in_addr;
  superblock sb;
  inode in;
  fileextent fe;
  int i;

  if (disk <= 0)
    return OPEN_DISK_FAILED;

  //Read superblock
  if(readBlock(disk , 0, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&sb, buf + 2, sizeof(superblock));

  if (isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;

  in_addr = getInodeAddress(FD);
  //Read Inode
  if(readBlock(disk, in_addr, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf+2, sizeof(inode));

  if(in.readonly)
    return FILE_IS_READONLY;

  release(sb.free_blocks, in_addr);
  cur_file = in.data_address;

  if(readBlock(disk, 1, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf + 2, sizeof(inode));
  for(i = 0; i < in.num_files; i++) {
    if(in_addr == in.entries[i].in_addr)
      break;
  }
  memmove(in.entries + i, in.entries + i + 1, (in.num_files - i) * sizeof(in_entry));
  in.num_files--;
  memcpy(buf + 2, &in, sizeof(inode));
  if(writeBlock(disk, 1, buf) < 0)
    return WRITE_BLOCK_FAILED;

  //Delete Inode
  buf[0] = FREE_TYPE;
  memset(buf+2, 0, DATA_SIZE);
  if(writeBlock(disk, getInodeAddress(FD), buf) < 0)
    return WRITE_BLOCK_FAILED;

  //Remove all File Extent Nodes
  while(1) {
    if(readBlock(disk, cur_file, buf) < 0)
      return READ_BLOCK_FAILED;
    memcpy(&fe, buf+2, sizeof(fileextent));
    len = fe.length;
    nxt_file = fe.nxtBlock;

    release(sb.free_blocks, cur_file);
    memset(buf+2, 0, DATA_SIZE);
    buf[0] = FREE_TYPE;
    if(writeBlock(disk, cur_file, buf) < 0)
      return WRITE_BLOCK_FAILED;
    cur_file = nxt_file;

    if(len)
      break;
  }

  removeTableEntry(FD);

  //Update Superblock with free blocks
  buf[0] = SUPERBLOCK_TYPE;
  memcpy(buf + 2, &sb, sizeof(superblock));
  if(writeBlock(disk, 0, buf) < 0)
    return WRITE_BLOCK_FAILED;

  return 0;
}

int tfs_readByte(fileDescriptor FD, char *buffer)
{
  unsigned char buf[BLOCKSIZE], addr;
  fileextent fe;
  inode in;
  int ptr;

  if (disk <= 0)
    return OPEN_DISK_FAILED;

  if (isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;

  //Read Inode Block
  if(readBlock(disk, getInodeAddress(FD), buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf+2, sizeof(inode));

  //Update access time for Inode
  in.finfo.access = time(NULL);
  buf[0] = INODE_TYPE;
  memcpy(buf + 2, &in, sizeof(inode));
  if(writeBlock(disk, getInodeAddress(FD), buf) < 0)
    return WRITE_BLOCK_FAILED;

  ptr = getFilePointer(FD);

  if(readBlock(disk, in.data_address, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&fe, buf+2, sizeof(fileextent));
  addr = fe.nxtBlock;
  while(ptr >= DATA_SIZE) {
    if(fe.length)
      return END_OF_FILE;
    if(readBlock(disk, addr, buf) < 0)
      return READ_BLOCK_FAILED;
    memcpy(&fe, buf+2, sizeof(fileextent));
    addr = fe.nxtBlock;

    ptr -= DATA_SIZE;
  }
  if(ptr >= fe.length - 1 && fe.length)
    return END_OF_FILE;

  *buffer = fe.data[ptr];

  setFilePointer(FD, getFilePointer(FD) + 1);

  return 0;
}

int tfs_seek(fileDescriptor FD, int offset)
{
  if (disk <= 0)
    return OPEN_DISK_FAILED;

  if (isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;

  setFilePointer(FD, offset);

  return 0;
}

int tfs_displayFragments(char * bitmap)
{
    unsigned char buf[BLOCKSIZE];
    int i;
    superblock sb;

    if (disk <= 0)
      return OPEN_DISK_FAILED;

    if(readBlock(disk, 0, buf) < 0)
      return READ_BLOCK_FAILED;
    memcpy(&sb, buf+2, sizeof(superblock));

    for(i = 0; i < sb.num_blocks; i++) {
      if(readBlock(disk, i, buf) < 0)
        return READ_BLOCK_FAILED;
      bitmap[i] = 48 + buf[0];
    }
    return 0;
}
