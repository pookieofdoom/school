/*
 * Copyright Software Innovations 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "SmartAlloc.h"
#define MAX_PER_LINE 4
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

typedef struct {
   UInt checksum;
   int charCount;
 

} CheckSumState;

typedef struct {
   int count;
   
} PrintState;


// CheckSum will take in a IntBlock and add up every value it obtains mod 65535.
void CheckSum(IntBlock *block, void *check) {
   
   ((CheckSumState *)check)->checksum +=  *block->data;
    ((CheckSumState *)check)->checksum =  ((CheckSumState *)check)->checksum % 65535;
 
   
   
   ((CheckSumState *)check)->charCount++; 
   
    
    
}



//PrintData will print out the data with capital hex in the IntBlocks but after 4 prints, it will print a newline and repeat this procedure. 

void PrintData(IntBlock *block, void *s) {
   
     
      
   
      if(((PrintState*)s)->count++ >= MAX_PER_LINE-1) {
   
       ((PrintState*)s)->count = 0;
       printf("%X\n", *block->data);

      }
      else {
      
      printf("%X ", *block->data);
      }

}




void bpInit(BitPacker *packer) {
   packer->packedData = 0;
   packer->bitsUsed = 0;
   packer->done = 0;
}


//bpPack now takes in a state and sink. Be sure to add the last actual parameter in main for the bpPack calls and so it matches 
//the required output. bpPack must be able to take in any type of state, not just the Config structure.
//IntBlock bpPack(BitPacker *packer, UInt data, int size) {
void bpPack(BitPacker *packer, UInt data, int size, void *state, void (*sink)(IntBlock*, void*)){
   IntBlock block;
   block.data = malloc(UINT_SIZE);

   
   
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
            sink(&block, state);
         }
         else {
            
            block.data[1] = packer->packedData<<UINT_SIZE - packer->bitsUsed ;
            sink(&block, state);
         }
        
         
     
   }
   else if(block.count > 0) {
     
      sink(&block, state);
      }
      
    free(block.data);
    //return block;

}


int main() {
   BitPacker bp1;
   BitPacker bp2;
   UInt data;
   CheckSumState cksum = {0, 0};
   PrintState print = {0};
   int size, count, idx;

   scanf("%d", &count);

   bpInit(&bp1);
   bpInit(&bp2);

   while (count--) {
      scanf("%u %d", &data, &size);
      bpPack(&bp1, data, size, &print, PrintData );
      
      bpPack(&bp2, data, size, &cksum, CheckSum );
      if (count == 1) {
         bp1.done = 1;
         bp2.done = 1;
      }
   }
   printf("\nCheckSum is: %d\n", cksum.checksum );
   printf("CharCount is: %d\n", cksum.charCount);

   printf("Allocated space: %u\n", report_space());
   return 0;
}
