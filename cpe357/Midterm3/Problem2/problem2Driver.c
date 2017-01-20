#include <stdio.h>

int main() {
   unsigned int value, at, bitValue;

   /* Read in test values */
   scanf("%x%d%d", &value, &at, &bitValue);

   /* Test... */
   setBit(&value, at, bitValue);

   /* Print results */
   printf("0x%08x\n", value);
   
   return 0;
}

