#include <stdio.h>
#include <stdlib.h>

int nextFree(unsigned char *vector, int len);

void reserve(unsigned char *vector, int pos);

void release(unsigned char *vector, int pos);

int numFree(unsigned char * vector, int len);
