#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "SmartAlloc.h"
#include "CodeSet.h"

typedef struct CodeEntry {
   unsigned char *point;
   unsigned short size;
   unsigned char data;
   struct CodeEntry *prefix; //need reference to prefix now
   int allocate; //flag to know if allocated data
  
} CodeEntry;

typedef struct CodeSet {
   CodeEntry *entry;
   int numCodes;
} CodeSet;


void *CreateCodeSet(int numCodes) {
   void *myCodeSet = calloc(1, sizeof(CodeSet));
   ((CodeSet *)myCodeSet)->entry = calloc(numCodes, sizeof(CodeEntry));
   ((CodeSet *)myCodeSet)->numCodes = 0;
   return myCodeSet;
}


int NewCode(void *codeSet, char val) {
   int index = ((CodeSet *)codeSet)->numCodes;
   (((CodeSet *)codeSet)->entry + index)->size = 1;
   
   //no longer need to allocate data in newCode
   (((CodeSet *)codeSet)->entry + index)->data = val;
   
   //increase numCodes by 1
   ((CodeSet *)codeSet)->numCodes += 1;
   
   //set allocation flag to 0 to denote that it has not been allocated yet
   (((CodeSet *)codeSet)->entry + index)->allocate = 0;
   return index;

}

int ExtendCode(void *codeSet, int oldCode) {
   int index = ((CodeSet *)codeSet)->numCodes;
   //increase the old code size by 1 for newly extended code
   (((CodeSet *)codeSet)->entry + index)->size = 
    (((CodeSet *)codeSet)->entry + oldCode)->size + 1;
    
   //no longer allocate data here
   //need to save the previous location (prefix)
   (((CodeSet *)codeSet)->entry + index)->prefix = 
    ((CodeSet *)codeSet)->entry + oldCode;
    
   //extend code by adding 0 to it
   (((CodeSet *)codeSet)->entry + index)->data = 0;
   ((CodeSet *)codeSet)->numCodes += 1;
   //set allocation flag to 0 since never allocated
   (((CodeSet *)codeSet)->entry + index)->allocate = 0;
   return index;

}

void SetSuffix(void *codeSet, int code, char suffix) {
   //no longer need to find the zero spot of extended code since it is 0
   (((CodeSet *)codeSet)->entry + code)->data = suffix;


}
//this function now needs to piece all the linked list and data together into a code
Code GetCode(void *codeSet, int code) {
   Code block; //will be the return
   int i;
   //have to allocate data for the block
   (((CodeSet *)codeSet)->entry + code)->point = 
    calloc((((CodeSet *)codeSet)->entry + code)->size, sizeof(char));
    
   //initializing the first code to initial points
   block.data = (((CodeSet *)codeSet)->entry + code)->point; //this line might be wrong
   block.size = (((CodeSet *)codeSet)->entry + code)->size;
   
   CodeEntry *temp = ((CodeSet *)codeSet)->entry + code;
   //looping and filling out the data of the block after the first one
   for (i = (((CodeSet *)codeSet)->entry + code)->size - 1; i >= 0; i--) {
      block.data[i] = temp->data;
      temp = temp->prefix;
   
   }
   
   //allocation flag is true since it has been allocated
   (((CodeSet *)codeSet)->entry + code)->allocate = 1;
   return block;
}


/* Mark the code at index |code| as no longer needed, until a new
 * GetCode call is made for that code. */
 
void FreeCode(void *codeSet, int code) {
   if ((((CodeSet *)codeSet)->entry + code)->allocate == 1) {
      //free that spot
      free((((CodeSet *)codeSet)->entry + code)->point);
      //allocation flag is now false
      (((CodeSet *)codeSet)->entry + code)->allocate = 0;
   
   }

}


void DestroyCodeSet(void *codeSet) {
   int i, sizeOfEntries = ((CodeSet *)codeSet)->numCodes;
   //data, entry, codeSet
   for (i = 0; i < sizeOfEntries; i++) {
      //check to see if spot is allocated which needs to be freed
      if (((CodeSet *)codeSet)->entry[i].allocate == 1) {
      
         free(((CodeSet *)codeSet)->entry[i].point);
      }
      
   }
   
   free(((CodeSet *)codeSet)->entry);
   free(codeSet);
}




