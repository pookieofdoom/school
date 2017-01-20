#include "LZWExp.h"
#include <stdio.h>
#include "CodeSet.h"
#include "SmartAlloc.h"

#define EOD 256
#define START 9
#define MAXBIT 4096
#define BITS_INTEGER 32

int findMax(int numBits) {
   int toReturn = 1;
   
   while (numBits--) {
      toReturn *= 2;
   }
   return toReturn - 1;
}

void InitDict(LZWExp *exp) {
   int count;
   
	for (count = 0; count <= EOD; count++) {
        newCode(exp->dict, count);
    }
}

int Decompress(LZWExp *exp, uint value) {
   Code newCode;
   
   if (exp->lastCode < value) {
      return BAD_CODE;
   }
   else if (exp->EODSeen && value) {
      return BAD_CODE;
   }
   else if (exp-> EODSeen && !value) {
      return 0;
   }
   else {
      if (value == EOD) {
         exp->EODSeen = 1;
         exp->sink(exp->sinkState, NULL, 0);
      }
      else {
         newCode = getCode(exp->dict, value);
         setSuffix(exp->dict, exp->lastCode, *newCode.data);
         exp->sink(exp->sinkState, newCode.data, newCode.size);
         return 1;
      }
   }
   return 0;
}

void ResetDict(LZWExp *exp) {
	destroyCodeSet(exp->dict);
   exp->dict = createCodeSet(MAXBIT);
   InitDict(exp);
   exp->lastCode = EOD;
   exp->numBits = START;
   exp->maxCode = findMax(exp->numBits);
}

void LZWExpInit(LZWExp *exp, DataSink sink, void *sinkState) {
   exp->dict = createCodeSet(MAXBIT);
   exp->sink = sink;
   exp->sinkState = sinkState;
   exp->numBits = START;
   exp->lastCode = EOD;
   exp->maxCode = findMax(exp->numBits);
   exp->leftover = 0;
   exp->bitsLeft = 0;
   exp->EODSeen = 0;
   InitDict(exp);
}

int LZWExpDecode(LZWExp *exp, uint bits) {
   uint value = 0;
   int doRecycle = 0, count, results;
   Code newCode;
   
   for (count = BITS_INTEGER; count >= exp->numBits; ) {
      if (exp->maxCode < exp->lastCode) {
         (exp->numBits)++;
         exp->maxCode = findMax(exp->numBits);
		}
      if (exp->lastCode >= MAXBIT - 1) {
			doRecycle = 1;
		}
           
		if (exp->bitsLeft && count == BITS_INTEGER) {
			count = exp->bitsLeft - exp->numBits + BITS_INTEGER;
			value = (exp->leftover << exp->numBits - 
			 exp->bitsLeft | bits >> count) & exp->maxCode;
      }
      else {
         value = bits >> count - exp->numBits & exp->maxCode;
         count -= exp->numBits; 
      }
  
      results = Decompress(exp, value);
      if (results == BAD_CODE) {
         return BAD_CODE;
      }
      else if (results == 1) {
         if (doRecycle) {
            ResetDict(exp);
            doRecycle = 0;
         }  
         else {
            (exp->lastCode)++;
            extendCode(exp->dict, value);
         }
      }
   }
 
   exp->leftover = bits;
   exp->bitsLeft = count;
   if (exp->EODSeen && bits & exp->maxCode >> exp->numBits - count) {
      return BAD_CODE;
   }
   
   return 0;
}

int LZWExpStop(LZWExp *exp) {
   if (exp->EODSeen) {
      return 0;
   }
   return NO_EOD_CODE;
}

void LZWExpDestruct(LZWExp *exp) {
   destroyCodeSet(exp->dict);
}
