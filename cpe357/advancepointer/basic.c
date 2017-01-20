#include <stdio.h>
#define UINT_SIZE 32
#define CHAR_SIZE 8 
#define CHAR_MAX 256
#define MAX_RANDOM_COUNT 100
#define SEED 42

typedef unsigned char UChar;
typedef unsigned int UInt;

typedef struct {
   UInt packedData;
   int bitsUsed;
   int done;
} BitPacker;

// Returns a random character. If called more than MAX_RANDOM_COUNT times, it returns EOF.
int RandomCode(UChar *code) {
   static int counter = 0;
  
   *code = rand() % CHAR_MAX;
   
   return (counter++ > MAX_RANDOM_COUNT) ? EOF : 0;
}

// ReadCode reads in a character from standard input and stores it into code. It also ignores white space. If there is no more input, return EOF.
int ReadCode(UChar *code) {
   
   return scanf(" %c", code);
}
// This function will take in a UInt and print it to screen in capital hex with a comma after it.
void printComma(UInt data) {
   printf("%X, ", data);
}


// This function will take in a UInt and print it to screen as a unsigned decimal with a bar (|) after it.
void printBar(UInt data) {
   printf("%u|", data);
}


// Same at bpInit from BitPackers Lab
void bpInit(BitPacker *packer) {
   packer->packedData = 0;
   packer->bitsUsed = 0;
   packer->done = 0;
}


// Similar to bpPack from BitPackers Lab except for its parameters and how it outputs data.  This version takes a function pointer for its source and another for its sink.  The source function
// takes a character pointer and returns an integer.  The sink will be a function pointer that takes in an UInt and returns nothing.
// This function will use the source to obtain a code and if the source returns EOF, don't do anything and return. When packedData has all bits used, you output using the sink.

//IntBlock bpPack(BitPacker *packer, UInt data, int size) {
void bpPack(BitPacker *packer, int (*source)(UChar *), void (*sink)(UInt)) { 
//void bpPack(BitPacker *packer, UChar input) {

   UChar input;
   
 
   if(source(&input)!=EOF) {

   if(packer->bitsUsed  <UINT_SIZE) {
      packer->packedData = packer->packedData<<CHAR_SIZE|input;
     
      packer->bitsUsed +=CHAR_SIZE;
     
     
      
   }
   
   if(packer->done==1 ) {
     // printf("%X ", packer->packedData<<UINT_SIZE-packer->bitsUsed);
        packer->packedData = packer->packedData<<UINT_SIZE-packer->bitsUsed;
        sink(packer->packedData);
   }
  
   else if(packer->bitsUsed == UINT_SIZE) {
        sink(packer->packedData);
        packer->bitsUsed = 0;
         packer->packedData = 0;
       
      }
 
    
                       
  }
   
      
      
}


int main() {
   int count;
   UChar data;
   BitPacker bp;

   srand(SEED);

   bpInit(&bp);

   scanf("%d", &count);

   while(count--) {
      if (count == 0) {
         bp.done = 1;
      }
      bpPack(&bp, ReadCode, printComma);
   }

   printf("\n");

   bpInit(&bp);

   scanf("%d", &count);

   while(count--) {
      if (count == 0) {
         bp.done = 1;
      }
     
      bpPack(&bp, RandomCode, printBar );
   }
   printf("\n");
   return 0;
}