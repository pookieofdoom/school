#include "LZWExp.h"
#include "CodeSet.h"


#define EOD 256
#define BIT_INIT 9
/* Function pointer to method to call when a block of bytes is
 * expanded and ready for transmission or whatever.  The void * parameter
 * can point to anything, and gives hidden information to the function 
 * so that it knows what file, socket, etc. the code is going to.  "Data"
 * points to the block of expanded bytes, with numBytes bytes in the block.
 * The block is not a C string -- it may have null characters in it, and
 * is not null-terminated.
 * 
 * A call with null "data" pointer marks the end of data, and will be the
 * final call.
*/



/* Initialize a LZWExp the DataSink to which to send uncompressed symbol 
 * sequences and an anonymous state object for the DataSink.
 */
void LZWExpInit(LZWExp *exp, DataSink sink, void *sinkState){
   int i;
   exp->sink = sink;
   exp->sinkState = sinkState;
   exp->numBits = BIT_INIT;
   exp->dict = CreateCodeSet(RECYCLE_CODE);
   exp->lastCode = EOD;
   exp->maxCode = 511;

   for(i =0; i<= EOD;i++) {
      NewCode(exp->dict, i);

   }

   buInit(&exp->bitUnpacker);
   exp->EODSeen = 0;


}

int DeCompress(LZWExp *exp, UInt bits ) {
   Code code;
   if(exp->lastCode < bits) {
      return BAD_CODE;

   } 
   else if(exp->EODSeen ) {
     return BAD_CODE:
  
   } 
   else {
       if(bits == EOD) {
          exp->EODSeen = 1;
          exp->sink(exp->sinkState, NULL, 0);
       }
      else {
          code = getCode(exp->dict, bits);
          setSuffx(exp->dict, exp->lastCode, *code.data);
          exp->sink(exp->sinkState, code.data, code.size);
          return 1;
     }
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
int LZWExpDecode(LZWExp *exp, UInt bits){
   UInt ret = 0;
   Code code;
   BitUnpacker bu = exp->bitUnpacker;
   buInit(&bu);
   buTakeData(&bu, bits);
   unpack(&bu, 32,&ret) ;
   
   
       




   return 0;

}



/* Mark end of decoding.  Returns 0 if all OK, or NO_EOD
 * if no terminating EOD code has been found 
 */
int LZWExpStop(LZWExp *exp) {
   if(exp->EODSeen){
      return 0;
   
   }
   return NO_EOD_CODE;

}

void LZWExpDestruct (LZWExp *exp) {
   DestroyCodeSet(exp->dict);


}