#include <stdio.h>
#include "MyLib.h"
#include "LZWExp.h"
#include "SmartAlloc.h"
#include <string.h>
#include <stdlib.h>
#define RFLAG "-R"

void PrintValue(void *format, unsigned char *data, int numBytes) {

   while (numBytes--) {
      printf(format, *data++);
   }
}

int main(int argc, char **argv) {
   UInt value = 0;
   int result = 0;
   int recycleCode = DEFAULT_RECYCLE_CODE;
   LZWExp exp;
   
   if (*(argv + 1) != NULL && strcmp(RFLAG, *(argv + 1))  == 0) {

      recycleCode = atoi(*(argv + 2));

   }
   
   LZWExpInit(&exp, PrintValue, "%c", recycleCode);

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
