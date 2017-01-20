#include "SmartAlloc.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "CodeSet.h"




//first define a CodeEntry, will look like a Code for now in Basic


typedef struct CodeEntry {
   char *data;
   unsigned short size;
} CodeEntry;


typedef struct CodeSet {
   CodeEntry *entry;
   int numCodes;
} CodeSet;


/* Allocate, initialize, and return a CodeSet object, via void *
 * The CodeSet will have room for |numCodes| codes, though it will
 * initially be empty. */ 
 
void *CreateCodeSet(int numCodes) {
   printf("Current space: %d\n", report_space());
   void *myCodeSet = calloc(1, sizeof(CodeSet));
   printf("Current space: %d\n", report_space());
   ((CodeSet *)myCodeSet)->entry = calloc(numCodes, sizeof(CodeEntry));
   printf("Current space: %d\n", report_space());
   printf("size of codeSet and size of Code Entry are %d and %d\n ",sizeof(CodeSet), sizeof(CodeEntry));
   ((CodeSet *)myCodeSet)->numCodes = 0;
   printf("Current space: %d\n", report_space());
   printf("create code set size of entries is %d\n", ((CodeSet *)myCodeSet)->numCodes);
   printf("Current space: %d\n", report_space());
   return myCodeSet;
}

/* Add a new 1-byte code to |codeSet|, returning its index, with
 * the first added code having index 0.  The new code's byte is
 * equal to |val|.  Assume (and assert, in order to pass style)
 * that there is room in the |codeSet| for a new code. */
 
int NewCode(void *codeSet, char val) {
   //get open spot in entry
   int index = ((CodeSet *)codeSet)->numCodes;
   //set the entry values
   
   (((CodeSet *)codeSet)->entry + index)->size = 1;
   (((CodeSet *)codeSet)->entry + index)->data = calloc(1,sizeof(char));
   *(((CodeSet *)codeSet)->entry + index)->data = val;
   //increase numCodes by 1
   printf("in new code size of entries is %d\n", ((CodeSet *)codeSet)->numCodes);
   ((CodeSet *)codeSet)->numCodes += 1;
   printf("in new code second time size of entries is %d\n", ((CodeSet *)codeSet)->numCodes);
   
   return index;
   
}


/* Create a new code by extending the existing code at index
 * by one zero-valued byte, using the linked structure from spec.  Any
 * existing code might be extended, not just the most recently
 * added one. Return the new code's index.  Assume |oldCode| 
 * is a valid index, and that there is enough room for 
 * a new code, but assert both of these conditions as well */
int ExtendCode(void *codeSet, int oldCode) {
   //get the spot where extended code goes to
   int i, index = ((CodeSet *)codeSet)->numCodes;
   printf("extend code first size of entries is %d\n", ((CodeSet *)codeSet)->numCodes);
   //increase the old code size by 1 for the newly extended code
   (((CodeSet *)codeSet)->entry + index)->size = 
    (((CodeSet *)codeSet)->entry + oldCode)->size + 1;
   
   printf("size is %d\n", (((CodeSet *)codeSet)->entry + oldCode)->size);
   printf("size is %d\n", (((CodeSet *)codeSet)->entry + index)->size);
   //allocate more space for the data
   (((CodeSet *)codeSet)->entry + index)->data = 
    calloc((((CodeSet *)codeSet)->entry + index)->size, sizeof(char));
   
   //copy the data over to the new spot
   
   for (i = 0; i < (((CodeSet *)codeSet)->entry + oldCode)->size; i++) 
      (((CodeSet *)codeSet)->entry + index)->data[i] = 
       (((CodeSet *)codeSet)->entry + oldCode)->data[i];
   
   //extended the code by adding a 0 to it
   printf("this is i %d", i);
   (((CodeSet *)codeSet)->entry + index)->data[i] = 0;
   
   ((CodeSet *)codeSet)->numCodes += 1;
   
   printf("extend code second size of entries is %d\n", ((CodeSet *)codeSet)->numCodes);
   return index;
   
     
}

/* Set the final byte of the code at index |code| to |suffix|.  
 * This is used to override the zero-byte added by extendCode. 
 * If the code in question has been returned by a getCode call,
 * and not yet freed via freeCode, then the changed final byte
 * will also show in the Code data that was returned from getCode.*/
void SetSuffix(void *codeSet, int code, char suffix) {
   //locating the final byte of the code 
   int zeroSpot = (((CodeSet *)codeSet)->entry + code)->size - 1;
   
   //setting the final byte of the code to suffix
   *((((CodeSet *)codeSet)->entry + code)->data + zeroSpot) = suffix;
}

/* Return the code at index |code| */
Code GetCode(void *codeSet, int code) {
   return *((Code *)(((CodeSet *)codeSet)->entry + code));
}

/* Free all dynamic storage associated with |codeSet| */
void DestroyCodeSet(void *codeSet) {
   //loop through entries and remove the data within them
   int i, sizeOfEntries = ((CodeSet *)codeSet)->numCodes;
   int ndx = 0;
   printf("size of entries is %d\n", ((CodeSet *)codeSet)->numCodes);
   for (i = 0; i < sizeOfEntries; i++) {
      printf("data destroyed will be ");
          ndx = 0;
          while(ndx <((CodeSet *)codeSet)->entry[i].size ){
            printf("%d ", *(((CodeSet *)codeSet)->entry[i].data+ndx));
            ndx++;
         }
         printf("\n");
      free( ((CodeSet *)codeSet)->entry[i].data);
     
   }
   //free the codeSet
    free( ((CodeSet *)codeSet)->entry);
   free(codeSet);
  
}
