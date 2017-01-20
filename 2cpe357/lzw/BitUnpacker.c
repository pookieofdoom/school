#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UINT_SIZE 32
#define UINT_MASK 0xFFFFFFFF

typedef unsigned int UInt;

typedef struct {
   UInt curData;
   UInt nextData;
   int bitsLeft;
   int validNext;
} BitUnpacker;

void BuInit(BitUnpacker *unpacker) {
   unpacker->curData = 0;
   unpacker->nextData = 0;
   unpacker->bitsLeft = 0;
   unpacker->validNext = 0;
}


void BuTakeData(BitUnpacker *unpacker, UInt set) {
   unpacker->nextData = set;
   unpacker->validNext = 1;

}


int BuUnpack(BitUnpacker *unpacker, int size, UInt *ret) {
   int end = 0;
   int mask = ~(UINT_MASK << size);

   if (unpacker->validNext) {
      unpacker->curData = unpacker->nextData;
      unpacker->validNext = 0;
      if (unpacker->bitsLeft) {

         *ret >>= (UINT_SIZE - size);
         *ret |= unpacker->curData >> (UINT_SIZE - unpacker->bitsLeft) &
          mask;
         unpacker->bitsLeft = UINT_SIZE - unpacker->bitsLeft;
         end++;
      }
      else {
         unpacker->bitsLeft = UINT_SIZE;

      }
   }



   if (unpacker->bitsLeft && !end) {

      if (unpacker->bitsLeft == UINT_SIZE) {
         *ret = unpacker->curData >> (unpacker->bitsLeft - size);
      }
      else {
         *ret = unpacker->curData >> (unpacker->bitsLeft - size) &
          mask;
      }


      if (unpacker->bitsLeft < size) {
         *ret = (unpacker->curData << (UINT_SIZE - unpacker->bitsLeft));
         unpacker->bitsLeft = size - unpacker->bitsLeft;
         end = 0;

      }
      else {
         unpacker->bitsLeft -= size;
         end++;
      }
   }

   return end;
}