/* Test driver for Problem 1.
 */
#include <stdio.h>

int main()
{
   unsigned int value, at;

   /* Read in test values */
   scanf("%x%d", &value, &at);

   /* Test and print results */
   printf("%d\n", getBit(value, at));

   return 0;
}

