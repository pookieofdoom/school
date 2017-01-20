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
   int i = 0;
   
   for (i = 0; i < numBits; i++) {
      maxCode *= 2;
   }
   //if i can include math.h  i can use pow
   return maxCode - 1;
}
//initial dictionary starts with 255 codes with EOD at 256
void InitDict(LZWExp *exp) {
   int i;
   
   for (i = 0; i <= EOD; i++) {
      NewCode(exp->dict, i);
   }

}


void LZWExpInit(LZWExp *exp, DataSink sink, void *sinkState, int recycleCode) {
   exp->dict = CreateCodeSet(MAXBIT);
   exp->sink = sink;
   exp->sinkState = sinkState;
   exp->lastCode = EOD; //EOD should be last code in initial dictionary
   exp->numBits = INITBITS; //initial num of bits of have which is 9 bits for 256 bits
   exp->maxCode = FindMaxCode(exp->numBits);
   exp->recycleCode = recycleCode;
   exp->EODSeen = 0;
   
   BuInit(&exp->bitUnpacker);
   InitDict(exp);   
}


/* Break apart compressed data in "bits" into one or more codes and send 
 * the corresponding symbol sequences to the DataSink.  Save any leftover 
 * compressed bits to combine with the bits from the next call of 
 * LZWExpEncode.  Return 0 on success or BAD_CODE if you receive a code not
 * in the dictionary.
 *
 * For this and all other methods, a code is "invalid" if it either could not
 * have been sent (e.g. is too high) or if it is a nonzero code following
 * the detection of an EOD code.
 */
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
      //set suffix
      if (exp->lastCode > EOD) {

         SetSuffix(exp->dict, exp->lastCode, *code.data);


      }
      //print the code -> send datasink
      exp->sink(exp->sinkState, code.data, code.size);

      //check if recycle dictionary

      
         //if not recycle dictionary, extend code
      exp->lastCode = ExtendCode(exp->dict, decode);
         //extend bit length of codes, if necessary
   
      if (exp->maxCode < exp->lastCode) {
         exp->numBits++;

         exp->maxCode = FindMaxCode(exp->numBits);
      }
      
      FreeCode(exp->dict, decode);
      
   }



   return 0;

   
}

/* Called after EOD has been seen to peform any error checking and/or
 * housekeeping that should be performed at the end of decoding. Returns 0 if
 * all is OK, NO_EOD if no terminating EOD code has been found, or BAD_CODE
 * if either non-zero bits follow the EOD or if one or more extra intextra an int-block(s) 
 */

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


/* Free all storage associated with LZWExp (not the sinkState, though,
 * which is "owned" by the caller.  Must be called even if LZWExpInit
 * returned an error.
 */
void LZWExpDestruct(LZWExp *exp) {
   DestroyCodeSet(exp->dict);
}
