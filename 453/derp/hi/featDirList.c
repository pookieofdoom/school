#include "tinyFS.h"

int tfs_rename(fileDescriptor FD, char *name) {
  int inode_addr, ind;
  inode in;
  char name_block[8];
  unsigned char buf[BLOCKSIZE];

  memset(buf, 0, BLOCKSIZE);

  if (isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;
  inode_addr = getInodeAddress(FD);

  readBlock(disk, inode_addr, buf);
  memcpy(&in, buf + 2, sizeof(inode));

  if (strlen(name) > 8)
    return NAME_TOO_LONG;

  memset(name_block, 0, 8);
  strncpy(name_block, name, 8);

  memset(in.name, 0, 8);
  strncpy(in.name, name, 8);

  memcpy(buf + 2, &in, sizeof(inode));
  if (writeBlock(disk, inode_addr, buf) < 0)
    return WRITE_BLOCK_FAILED;

  readBlock(disk, 1, buf);
  memcpy(&in,buf+2, sizeof(inode));
  for(ind = 0; ind < in.num_files; ind++){
    if(in.entries[ind].in_addr == inode_addr) {
      memset(in.entries[ind].name, 0, 8);
      memcpy(in.entries[ind].name, name_block, 8);
    }
  }
  memcpy(buf + 2, &in, sizeof(inode));
  writeBlock(disk, 1, buf);

  return 0;
}

//filenames will be a list of strings of size 9 of length numFiles.  It
// is the responsibility of the caller to allocate the memory for filenames.
int tfs_readDir(char ** filenames, int *numFiles) {
  unsigned char buf[BLOCKSIZE];
  int i;
  superblock sb;
  inode in;
  char * ptr;

  if(readBlock(disk, 0, buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&sb, buf+2, sizeof(superblock));

  *filenames = (char *)calloc(sizeof(char) * 9, 1);
  ptr = *filenames;

  *numFiles = 0;
  for(i = 0; i < sb.num_blocks; i++) {
    memset(buf, 0, BLOCKSIZE);
    if(readBlock(disk, i, buf) < 0)
      return READ_BLOCK_FAILED;
    if(buf[0] == INODE_TYPE) {
      memcpy(&in, buf+2, sizeof(inode));
      *numFiles += 1;
      *filenames = (char *)realloc(*filenames, sizeof(char) * 9 * *numFiles);
      ptr = *filenames + sizeof(char) * 9 * (*numFiles - 1);
      strncpy(ptr, in.name, 8);
    }
  }
  return 0;
}
