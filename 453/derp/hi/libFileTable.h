#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TinyFS_errno.h"

typedef struct descentry {
    int FD;
    unsigned int inode_addr;
    unsigned int fptr;
} descentry;


int makeTableEntry(int in_loc);

int isFileOpen(int FD);

int getInodeAddress(int FD);

int getFileDescriptor(unsigned char inode_addr);

int getFilePointer(int FD);

int setFilePointer(int FD, int fp);

int removeTableEntry(int FD);

void clearTable();
