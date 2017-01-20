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

int getMax (int bits) {
   int max = 1;
   while(bits--)
      max = max * 2;
   return max -1;


}
/*int DeCompress(LZWExp *exp, UInt bits ) {
   Code code;
   printf("hi\n");
   if(exp->lastCode < bits) {
      printf("%d\n", bits);
      printf("%d\n", exp->lastCode);
       printf("huh\n");
      return BAD_CODE;

   } 
   else if(exp->EODSeen && !bits) {
     
     return 0;
  
   } 
   else if(exp->EODSeen && bits) {
      return BAD_CODE;
   }
   
   else {
       if(bits == EOD) {
          exp->EODSeen = 1;
          exp->sink(exp->sinkState, NULL, 0);
       }
      else {
          code = GetCode(exp->dict, bits);
          SetSuffix(exp->dict, exp->lastCode, *code.data);
          exp->sink(exp->sinkState, code.data, code.size);
          return 1;
      }
   }
   return 0;
   }*/
   
   
void RecycleDict (LZWExp *exp) {
   int i = 0;
	DestroyCodeSet(exp->dict);
   exp->dict = CreateCodeSet(RECYCLE_CODE);
   for(i =0; i<= EOD;i++) {
      NewCode(exp->dict, i);

   }

   exp->lastCode = EOD;
   exp->numBits = BIT_INIT;
   exp->maxCode = getMax(exp->numBits);
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
/*int LZWExpDecode(LZWExp *exp, UInt bits){
   UInt ret = 0;
   int recycle = 0, size, isValid, detect;
   Code code;
   BitUnpacker bu = exp->bitUnpacker;
   buTakeData(&bu, bits);
  
   for(size = 32; size >= exp->numBits;) {
      if(exp->maxCode < exp->lastCode) {
         printf("max code is %d\n", exp->maxCode);
         (exp->numBits)++;
         exp->maxCode = getMax(exp->numBits);
 
      }
      
     
      else {
         printf("%d\n", ret);
         isValid = unpack(&bu, size, &ret) ;
        
      
      }
     detect = DeCompress(exp, ret);
     printf("%d\n", ret);
     if(detect == BAD_CODE) {
      printf("blah\n");
    
        return BAD_CODE;
     }
     
       
         else {
            (exp->lastCode)++;
            ExtendCode(exp->dict, bits);
      
         }
     
     

     
     
   }  
   
   if(!isValid && exp->EODSeen ) {
      printf("huh\n");
     
      return BAD_CODE;
   }  




   return 0;

}
*/

//LZWDecode Reference Code

int LZWExpDecode(LZWExp *exp, UInt bits){

UInt code;
Code entry;

buTakeData(&exp->bitUnpacker  , bits);

while(unpack(&exp->bitUnpacker, exp->numBits  ,&code) ) {

   if(exp->EODSeen || code > exp->lastCode )
      return BAD_CODE;
      
   else if(code == EOD ) {
      exp->EODSeen =  1;
      return 0;
   }

   entry = GetCode (exp->dict, code);
//void SetSuffix(void *codeSet, int code, char suffix);
    if(exp->lastCode > EOD)
      SetSuffix(exp->dict, exp->lastCode, *entry.data);

    exp->sink(exp->sinkState, entry.data, entry.size);
      
   if(exp->lastCode == RECYCLE_CODE - 1) 
      RecycleDict(exp);
      
    else {
      //int ExtendCode(void *codeSet, int oldCode);
      exp->lastCode = ExtendCode(exp->dict, code);
      if(exp->lastcode > exp->maxCode)
      (exp->numbits)++
      exp->maxCode = exp->maxCode <<1 | 1;
   }
   
    freecode(exp->dict,code);
   
   }
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