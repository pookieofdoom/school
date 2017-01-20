#include "LZWExp.h"
#include <stdio.h>
#include "CodeSet.h"
#include "BitUnpacker.h"
#include "SmartAlloc.h"

#define EOD 256
#define INITBITS 9
#define MAXBIT 4096
#define BITS_INTEGER 32
  
int FindMaxCode(int numBits) {
   int maxCode = 1;
   int i;
   
   for (i = 0; i < numBits; i++) {
      maxCode *= 2;
   }
   return maxCode - 1;
}

void InitDict(LZWExp *exp) {
   int i;
   
   for (i = 0; i <= EOD; i++) {
      NewCode(exp->dict, i);
   }
}

void RecycleDict(LZWExp *exp) {
   exp->lastCode = EOD;
   exp->numBits = INITBITS;
   exp->maxCode = FindMaxCode(exp->numBits);
   //destroy old codeset and recreate
   DestroyCodeSet(exp->dict);
   exp->dict = CreateCodeSet(exp->recycleCode);
   InitDict(exp);
}

void LZWExpInit(LZWExp *exp, DataSink sink, void *sinkState, int recycleCode) {
   exp->dict = CreateCodeSet(recycleCode);
   exp->sink = sink;
   exp->sinkState = sinkState;
   exp->lastCode = EOD; 
   exp->numBits = INITBITS; 
   exp->maxCode = FindMaxCode(exp->numBits);
   exp->recycleCode = recycleCode;
   exp->EODSeen = 0;
   
   BuInit(&exp->bitUnpacker);
   InitDict(exp);   
}

int LZWExpDecode(LZWExp *exp, UInt bits) {
   UInt decode;
   Code code;
   
   BuTakeData(&exp->bitUnpacker, bits);
   while (BuUnpack(&exp->bitUnpacker, exp->numBits, &decode)) {
      if (decode > exp->lastCode || exp->EODSeen) {
         return BAD_CODE;
      }
      else if (decode == EOD) {
         exp->EODSeen = 1;
         return 0;
      }

      code = GetCode(exp->dict, decode);  
      if (exp->lastCode > EOD) {
         SetSuffix(exp->dict, exp->lastCode, *code.data);
      }
      exp->sink(exp->sinkState, code.data, code.size);
      
      if (exp->lastCode == exp->recycleCode - 1) {
         RecycleDict(exp);
      }
      else {
         exp->lastCode = ExtendCode(exp->dict, decode);
  
         if (exp->maxCode < exp->lastCode) {
            exp->numBits++;
            exp->maxCode = FindMaxCode(exp->numBits);
         }
      }
      
      FreeCode(exp->dict, decode);    
   }
   return 0; 
}

int LZWExpStop(LZWExp *exp) {
   if (!exp->EODSeen) {
      return MISSING_EOD;
   }
   
   if (exp->bitUnpacker.bitsLeft && 
    (exp->bitUnpacker.curData << (UINT_SIZE - exp->bitUnpacker.bitsLeft))) {

      return BAD_CODE;
   }

   return 0;
}

void LZWExpDestruct(LZWExp *exp) {
   DestroyCodeSet(exp->dict);
}
