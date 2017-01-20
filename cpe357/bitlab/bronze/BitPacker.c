/*
 * Copyright Software Inventions 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT_SIZE 32

typedef unsigned int UInt;

typedef struct {
   UInt *data;
   int count;
} IntBlock;

typedef struct {
   UInt packedData;
   int bitsUsed;
   int done;
} BitPacker;


void bpInit(BitPacker *packer) {
   packer->packedData = 0;
   packer->bitsUsed = 0;
   packer->done = 0;
}


IntBlock bpPack(BitPacker *packer, UInt data, int size) {
   IntBlock block;
   block.data = malloc(UINT_SIZE*2);

   
   
      if(packer->bitsUsed + size <= UINT_SIZE) {
         packer->packedData = packer->packedData<<size|data;
      }
      else {
          
          packer->packedData = (packer->packedData<<(UINT_SIZE - packer->bitsUsed))|(data>>size - (UINT_SIZE - packer->bitsUsed));
       
      
      
      }
      packer->bitsUsed +=size;
      *block.data = packer->packedData;
      
       block.count= packer->bitsUsed / UINT_SIZE;
      if(packer->bitsUsed > UINT_SIZE) {
         packer->bitsUsed -= UINT_SIZE;
         packer->packedData = 0;
         packer->packedData = packer->packedData | data;
       
         
      }
      else if(packer->bitsUsed == UINT_SIZE) {
         packer->bitsUsed = 0;
         packer->packedData = 0;
      }
   
      
   if(packer->done==1 ) {
       if(packer->bitsUsed % UINT_SIZE)
       
         block.count++;
        
         if(block.count <2) {
            *block.data = *block.data << UINT_SIZE - packer->bitsUsed;
         }
         else {
            
            block.data[1] = packer->packedData<<UINT_SIZE - packer->bitsUsed ;
         }
        
         
     
   }
   
    return block;

}




int main() {
   BitPacker bp;
   IntBlock iB;
   UInt data;
   int size, count, idx;

   scanf("%d", &count);

   bpInit(&bp);
   while (count--) {
      scanf("%u %d", &data, &size);
      iB = bpPack(&bp, data, size);
      for (idx = 0; idx < iB.count; idx++) {
         printf("%x ", *(iB.data + idx));
      }
      free(iB.data);
      if (count == 1) {
         bp.done = 1;
      }
   }
   printf("\n");
   //printf("Allocated space left: %d\n", report_space());
   return 0;
}