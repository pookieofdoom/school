#include <stdio.h>
#include <string.h>

#define NUM_VALS 35
#define SHORT_SIZE 16
#define CHAR_BITS 7
#define SHORT_LEFTOVER 9

#define malloc NOT_ALLOWED
#define calloc NOT_ALLOWED

int main() {
   unsigned short *ptr, vals[NUM_VALS], letter = 0;
   int temp, mask, bits;
   
   memset(vals, 42, NUM_VALS*sizeof(short));
   memset(vals, 0, NUM_VALS*sizeof(short));
   
   bits = SHORT_SIZE;
   ptr = &vals[NUM_VALS - 1];
   

   while ( ptr >= vals )
   {
      scanf("%c", &letter);
      if ( bits >= CHAR_BITS)
      {
         *ptr |= letter << SHORT_SIZE - bits;
          bits -= CHAR_BITS;
      }
      else
      {  

         *(ptr) |= letter << SHORT_SIZE - bits;
         ptr--;
         *ptr |= letter >> bits;
         bits = SHORT_SIZE - (CHAR_BITS - bits);
      }
   } 
   
   
   bits = SHORT_SIZE;
   ptr = vals;
   mask = 0x0000007F;
   
   
   while (ptr < &vals[NUM_VALS])
   {
      letter = 0; 
      if (bits < CHAR_BITS)
      {
         letter |= ptr[-1] << CHAR_BITS - bits;
         bits = SHORT_SIZE - (CHAR_BITS - bits);
         letter |= *ptr >> bits;


      }
      else
      {
         bits -= CHAR_BITS;
         letter |= *ptr >> bits;

      }          
      letter &= mask;
      printf("%c", letter);
      if ( bits < CHAR_BITS)
      {
        ptr++;
      }
   }
   return 0;
}
