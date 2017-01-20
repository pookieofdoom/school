#include <stdio.h>
#include "SmartAlloc.h"
#include "LZWExp.h"
#include "MyLib.h"

void Displayvalue(void *format, char *data, int numBytes) {
   if (data != NULL) {
      for (; numBytes; --numBytes) {
         printf(format, *data++);
      }
   }
}

int main() {
   UInt value = 0;
   int result = 0, scanfResult = 1, bitsLeft, check = 1;
   LZWExp exp;

   LZWExpInit(&exp, Displayvalue, "%c");
   scanfResult = scanf("%x", &value);
   while (result == 0 && scanfResult != EOF) {
      if (scanfResult == 0) {
         result = BAD_CODE;
      }
      else if (scanfResult != EOF) {
         result = LZWExpDecode(&exp, value);
      }
      scanfResult = scanf("%x", &value);
   }  

   bitsLeft = exp.bitUnpacker.bitsLeft;
   while (bitsLeft--) {
      check *= 2;
   }
   check--;
   
   if (exp.bitUnpacker.bitsLeft & check) {
      printf("Bad code\n");
   }
   else if (result == BAD_CODE) {
      printf("Bad code\n");
   }
   else if (LZWExpStop(&exp) == NO_EOD_CODE) {
      printf("Missing EOD\n");
   }

   LZWExpDestruct(&exp);
   if ( report_space()) {
        printf("%lu\n", report_space());
   }
   
   return 0;
}
