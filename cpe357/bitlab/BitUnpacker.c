/*
 * Copyright Software Innovationscurrent
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT_SIZE 32
#define UINT_MASK 0xFFFFFFFF
#define CHAR_SIZE 8
#define CHAR_MASK 0xFF

typedef unsigned int UInt;

/*
   Have current int block and next int block
   Returns a code through an out parameter
   Return true if you can return a code return false if you need another int block
*/

typedef struct {
   UInt curData;
   UInt nextData;
   int bitsLeft;
   int validNext;
} BitUnpacker;


void buInit(BitUnpacker *unpacker) {
   unpacker->curData = 0;
   unpacker->nextData = 0;
   unpacker->bitsLeft = 0;
   unpacker->validNext = 0;
}


void buTakeData(BitUnpacker *unpacker, UInt set) {
   unpacker->nextData = set;
   unpacker->validNext = 1;
   
}

int unpack (BitUnpacker *unpacker, UInt *ret) {

   //sets its curData to the next data if its valid
   if(unpacker->validNext) {
      unpacker->curData = unpacker->nextData;
      unpacker->bitsLeft = UINT_SIZE;
      unpacker->validNext = 0;
      
   
 
   }
   
   
   //actually upacking, then return 1
   if(unpacker->bitsLeft !=0) {
   
      *ret = unpacker->curData >> unpacker->bitsLeft -CHAR_SIZE & CHAR_MASK;
     
      unpacker->bitsLeft -= CHAR_SIZE;
      return 1;
   }
   return 0;
}







int main() {
   BitUnpacker bu;
   int numBlocks, size, i, count;
   UInt ret;
   UInt *temp;

   scanf("%d", &numBlocks);

   temp = calloc(sizeof(UInt), numBlocks);

   for (i = 0; i < numBlocks; i++) {
      scanf(" %x", &temp[i]);
   }

   buInit(&bu);
   i = 0;

   count = numBlocks * 4;

   while (count--) {
      if (!unpack(&bu, &ret)) {
         if (i < numBlocks) {
            buTakeData(&bu, temp[i++]);
            unpack(&bu, &ret);
         }
         else {
            printf("Not enough data left.\n");
         }
      }
      printf(" %08X", ret);
   }
   printf("\n");
   free(temp);

   return 0;
}