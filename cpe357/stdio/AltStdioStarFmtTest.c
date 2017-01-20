
#include "AltStdio.h"
/* Explicit prototype of scanf used in main due to the fact we can't
 * include stdio.h for this problem.
 */
int scanf(const char*, ...);

int main() {
   char cVal;
   unsigned int uVal, field;
   char sVal[100];
   
   while (EOF != scanf("%d %s %u %c", &field, sVal, &uVal, &cVal))
      altFprintf(altStdout, "Field size %i: %*s%*i%*c\n",
       field, field, sVal, field, uVal, field, cVal);
 
   altFflush(altStdout);

   return 0;
}
