#include <stdio.h>

#define BITS_PER_SHORT 16
int main() {
   short num = 0;
   int numPairs = 0;
   int lastBit = 0;
   
   while(scanf("%hd", &num) == 1) {
      int mask = BITS_PER_SHORT;
      while(mask) {
         int bit1 = mask == BITS_PER_SHORT ? lastBit : num & 1 << mask;
         lastBit = num & 1 << --mask;
         if(bit1 && lastBit)
            numPairs++;
      }
   }
   printf("%d pairs\n", numPairs);
   
   return 0;
}