#include "tinyFS.h"

int tfs_makeRO(char * name) {
  unsigned char buf[BLOCKSIZE];
  char name_block[8];
  superblock sb;
  inode in, in2;
  int ind;

  memset(buf, 0, BLOCKSIZE);
  memset(name_block, 0, 8);

  if (strlen(name) > 8)
    return NAME_TOO_LONG;

  memcpy(name_block, name, strlen(name));

  if (readBlock(disk, 0, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&sb, buf+2, sizeof(superblock));

  if (readBlock(disk, 1, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf + 2, sizeof(inode));

  for(ind = 0; ind < in.num_files; ind++) {
    if(strncmp(name_block, in.entries[ind].name, 8) == 0) {
      if (readBlock(disk, in.entries[ind].in_addr, buf) < 0)
        return READ_BLOCK_FAILED;
      memcpy(&in2, buf + 2, sizeof(inode));
      in2.readonly = 1;
      memcpy(buf + 2, &in2, sizeof(inode));
      if(writeBlock(disk, in.entries[ind].in_addr, buf))
        return WRITE_BLOCK_FAILED;
      return 0;
    }
  }

  return NO_SUCH_FILE;
}

int tfs_makeRW(char * name) {
  unsigned char buf[BLOCKSIZE];
  char name_block[8];
  superblock sb;
  inode in, in2;
  int ind;

  memset(buf, 0, BLOCKSIZE);
  memset(name_block, 0, 8);

  if (strlen(name) > 8)
    return NAME_TOO_LONG;

  memcpy(name_block, name, strlen(name));

  if (readBlock(disk, 0, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&sb, buf+2, sizeof(superblock));

  if (readBlock(disk, 1, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf + 2, sizeof(inode));

  for(ind = 0; ind < in.num_files; ind++) {
    if(strncmp(name_block, in.entries[ind].name, 8) == 0) {
      if (readBlock(disk, in.entries[ind].in_addr, buf) < 0)
        return READ_BLOCK_FAILED;
      memcpy(&in2, buf + 2, sizeof(inode));
      in2.readonly = 0;
      memcpy(buf + 2, &in2, sizeof(inode));
      if(writeBlock(disk, in.entries[ind].in_addr, buf))
        return WRITE_BLOCK_FAILED;
      return 0;
    }
  }
  return NO_SUCH_FILE;
}

int tfs_writeByte(fileDescriptor FD, unsigned char data) {
  unsigned char buf[BLOCKSIZE], addr;
  fileextent fe;
  inode in;
  int ptr;

  addr = 0;

  if (disk <= 0)
    return OPEN_DISK_FAILED;

  if (isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;

  //Read Inode Block
  if(readBlock(disk, getInodeAddress(FD), buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf+2, sizeof(inode));

  if(in.readonly)
    return FILE_IS_READONLY;

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
  while(ptr >= DATA_SIZE) {
    addr = fe.nxtBlock;
    if(fe.length)
      return END_OF_FILE;
    if(readBlock(disk, addr, buf) < 0)
      return READ_BLOCK_FAILED;
    memcpy(&fe, buf+2, sizeof(fileextent));

    ptr -= DATA_SIZE;
  }
  if(ptr >= fe.length - 1 && fe.length)
    return END_OF_FILE;

  if(addr == 0)
    addr = in.data_address;

  fe.data[ptr] = data;
  memcpy(buf + 2, &fe, sizeof(fe));
  if(writeBlock(disk, addr, buf) < 0)
    return WRITE_BLOCK_FAILED;

  setFilePointer(FD, getFilePointer(FD) + 1);

  return 0;
}
