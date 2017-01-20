#include "BitUnpacker.h"

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
   UInt mask = ~(UINT_MASK << size);

   if (unpacker->validNext) {

      if (unpacker->bitsLeft && unpacker->bitsLeft < size) {

         *ret = (unpacker->curData << (UINT_SIZE - unpacker->bitsLeft));
         unpacker->bitsLeft = size - unpacker->bitsLeft;

      }
      
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

      if (unpacker->bitsLeft >= size) {
         unpacker->bitsLeft -= size;
         end++;
      }
   }
   return end;
}