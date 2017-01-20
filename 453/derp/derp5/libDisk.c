#include "libDisk.h"

int openDisk(char *filename, int nBytes)
{
	int disk, i;

  unsigned char buf[BLOCKSIZE];
  memset(buf, 0, BLOCKSIZE);

  disk = open(filename, O_RDWR | O_CREAT, 0666);
  //Initialize file to all zeros if nBytes = 0
  if(nBytes > 0) {
    for(i = 0; i < nBytes / BLOCKSIZE; i++) {
      if (write(disk, buf, BLOCKSIZE) < 0) {
        return -1;
      }
    }
  }
  return disk;
}

int readBlock(int disk, int bNum, void *block)
{
  int offset;

  offset = lseek(disk, bNum * BLOCKSIZE, SEEK_SET);
  if(offset < 0)
    return -1;

  if (read(disk, (unsigned char*)block , BLOCKSIZE) < BLOCKSIZE)
    return -1;
  return 0;
}

int writeBlock(int disk, int bNum, void *block)
{
  int offset;

  offset = lseek(disk, bNum * BLOCKSIZE, SEEK_SET);
  if(offset < 0)
    return -1;

  if (write(disk, (unsigned char *)block, BLOCKSIZE) < 0)
    return -1;
  return 0;
}

void closeDisk(int disk)
{
  close(disk);
}
