#include <stdio.h>
#define UINT_SIZE 32
#define CHAR_SIZE 8 

typedef unsigned char UChar;
typedef unsigned int UInt;

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


void bpPack(BitPacker *packer, UChar input) {
   if(packer->bitsUsed  <UINT_SIZE) {
      packer->packedData = packer->packedData<<CHAR_SIZE|input;
     
      packer->bitsUsed +=CHAR_SIZE;
     
     
      
   }
   
   if(packer->done==1 ) {
      printf("%X ", packer->packedData<<UINT_SIZE-packer->bitsUsed);
   }
  
   else if(packer->bitsUsed == UINT_SIZE) {
        printf("%X ", packer->packedData);
        packer->bitsUsed = 0;
         packer->packedData = 0;
       
      }
 
  
}

int main() {
   int count;
   UChar data;
   BitPacker bp; 


   bpInit(&bp);
   
   scanf("%d", &count);

   while(count--) {
      scanf(" %c", &data);
      bpPack(&bp, data);
      if (count == 1) {
         bp.done = 1;
      }   
   }   
   printf("\n");
   return 0;
}