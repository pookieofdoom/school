#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "SmartAlloc.h" // #include "SmartAlloc.h" if not on IHS

#define MAX_PER_LINE 4
#define UINT_SIZE 32

typedef unsigned int UInt;

// Write state variable type declarations if needed, and output functions

typedef struct {
   UInt checksum;
   int charCount;
 

} CheckSumState;

typedef struct {
   int count;
   
} PrintState;


void CheckSum(UInt data, void *check) {
   
   ((CheckSumState *)check)->checksum +=  data;
    ((CheckSumState *)check)->checksum =  ((CheckSumState *)check)->checksum % 65535;
 
   
   
   ((CheckSumState *)check)->charCount++; 
   
    
    
}

void PrintData(UInt data, void *s) {
   
     
      
   
      if(((PrintState*)s)->count++ >= MAX_PER_LINE-1) {
   
       ((PrintState*)s)->count = 0;
       printf("%08X\n", data);

      }
      else {
      
      printf("%08X ", data);
      }

}


// Declare BitPacker type, and write BpInit to initialize it
typedef struct {
   UInt packedData;
   int bitsUsed;
   void *state;
   void (*sink)(UInt, void*);

} BitPacker;

void BpInit(BitPacker *packer, void (*sink) (UInt, void*), void *state) {
   packer->packedData = 0;
   packer->bitsUsed = 0;
   packer->state = state;
   packer->sink = sink;
}

// BpPacker.  Pack a code of a given bitsize.
void BpPack(BitPacker *packer, UInt data, int size) {
   if(packer->bitsUsed + size <= UINT_SIZE) {
      packer->packedData <<= size;
      packer->packedData |= data;
 
      
   }
   else {

      packer->packedData <<= (UINT_SIZE - packer->bitsUsed);
      packer->packedData |= (data >> (size - (UINT_SIZE - packer->bitsUsed)));
       

   }
   packer->bitsUsed += size;

   if (packer->bitsUsed > UINT_SIZE) {
      packer->bitsUsed -= UINT_SIZE;
      packer->sink(packer->packedData, packer->state);
      packer->packedData = 0;
      packer->packedData |= data;
   }
   /* for some reaosn not needed for test cases but might need later??
   if(packer->bitsUsed == UINT_SIZE) {
      packer->sink(packer->packedData, packer->state);
      packer->bitsUsed = 0;
      packer->packedData = 0;
   }
   */
}


// BPStop.  Do any final cleanup needed, assuming no more BpPack calls will occur
void BpStop(BitPacker *packer) {
   if (packer->packedData) {                                                     // Base: 3, Surcharge: 0
      packer->packedData = packer->packedData << (UINT_SIZE - packer->bitsUsed); // Base: 7, Surcharge: 0
      packer->sink(packer->packedData, packer->state);                                                  // Base: 3, Surcharge: 0
   }  
}


int main() {
   BitPacker bp1;
   BitPacker bp2;
   UInt data;
   int size, count;

   // State variable declaration and initialization
   CheckSumState cksum;
   PrintState print;
   cksum.checksum = 0;
   cksum.charCount = 0;
   print.count = 0;



   scanf("%d", &count);

   BpInit(&bp1, PrintData, &print);
   BpInit(&bp2, CheckSum, &cksum);

   while (count--) {
      scanf("%u %d", &data, &size);
      BpPack(&bp1, data, size);
      BpPack(&bp2, data, size);
   }
   BpStop(&bp1);
   BpStop(&bp2);

   printf("\nCheckSum is: %d\n", cksum.checksum);
   printf("Int count is: %d\n", cksum.charCount);


   printf("Allocated space: %ld\n", report_space());

   return 0;
}