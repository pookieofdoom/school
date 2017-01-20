#include "libFreeBlocks.h"

int nextFree(unsigned char *vector, int len) {
  int i, j;
  j = 0;
  for(i = 0; i < len; i++) {
    if (!((vector[i / 8] >> (7 - j)) & 0x01))
      return i;
    if (j % 8 == 7)
      j = 0;
    else
      j++;
  }
  return -1;
}

void reserve(unsigned char *vector, int pos) {
  vector[pos / 8] |= 0x01 << (7 - (pos % 8));
}

void release(unsigned char *vector, int pos) {
  vector[pos / 8] &= ~(0x01 << (7 - (pos % 8)));
}

int numFree(unsigned char *vector, int len) {
  int i, j, num_free;
  j = 0;
  for(i = 0; i < len; i++) {
    if (!((vector[i / 8] >> (7 - j)) & 0x01))
      num_free++;
    if (j % 8 == 7)
      j = 0;
    else
      j++;
  }
  return num_free;
}
