#include <stdio.h>
#include "MyLib.h"
#include "LZWExp.h"
#include "SmartAlloc.h"

void PrintValue(void *format, unsigned char *data, int numBytes) {
   if (data != NULL) {
      for (; numBytes; --numBytes) {
         printf(format, *data++);
      }
   }
}

int main() {
   UInt value = 0;
   int result = 0;
   LZWExp exp;
   LZWExpInit(&exp, PrintValue, "%c", DEFAULT_RECYCLE_CODE);

   while (!result && scanf("%08X", &value) != EOF) {
      result = LZWExpDecode(&exp, value);
   }  

   if (result == BAD_CODE || LZWExpStop(&exp) == BAD_CODE) {
      printf("Bad code\n");
   }
   else if (LZWExpStop(&exp) == MISSING_EOD) {
      printf("Missing EOD\n");
   }

   LZWExpDestruct(&exp);
   if (report_space()) {
      printf("%ld\n", report_space());
   }

   
   return 0;
}
