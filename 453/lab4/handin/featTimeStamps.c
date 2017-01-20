#include "tinyFS.h"

int tfs_readFileInfo(fileDescriptor FD, fileinfo * finfo) {
  unsigned char buf[BLOCKSIZE];
  inode in;

  if (disk <= 0)
    return OPEN_DISK_FAILED;

  if (isFileOpen(FD) < 0)
    return FILE_NOT_OPEN;

  //Read Inode Block
  if(readBlock(disk, getInodeAddress(FD), buf) < 0)
    return READ_BLOCK_FAILED;
  memcpy(&in, buf+2, sizeof(inode));

  memcpy(finfo, &in.finfo, sizeof(fileinfo));
  return 0;
}
