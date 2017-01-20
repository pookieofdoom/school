
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "SmartAlloc.h"
#include "CodeSet.h"

typedef struct CodeEntry {
   unsigned char *point;
   unsigned short size;
   unsigned char data;
   struct CodeEntry *prefix;
   int allocate;

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
   CodeSet *myCodeSet = (CodeSet *)codeSet;
   CodeEntry *myEntry = myCodeSet->entry + myCodeSet->numCodes++;
   myEntry->size = 1;
   myEntry->data = val;
   myEntry->allocate = 0;
   return myCodeSet->numCodes - 1;

}

int ExtendCode(void *codeSet, int oldCode) {
   CodeSet *myCodeSet = (CodeSet *)codeSet;
   int index = myCodeSet->numCodes;
   CodeEntry *myEntry = myCodeSet->entry + index;
   CodeEntry *oldEntry = myCodeSet->entry + oldCode;
   myEntry->size = oldEntry->size + 1;
   myEntry->prefix = oldEntry;
   myEntry->data = 0;
   myEntry->allocate = 0;
   myCodeSet->numCodes++;
   return index;

}

void SetSuffix(void *codeSet, int code, char suffix) {
   CodeSet *myCodeSet = (CodeSet *)codeSet;
   CodeEntry *myEntry = myCodeSet->entry + code;
   if (myEntry->point != NULL) {
      myEntry->point[myEntry->size - 1] = suffix;
   }
   myEntry->data = suffix;
}   

Code GetCode(void *codeSet, int code) {
   Code block;
   int i;
   CodeSet *myCodeSet = (CodeSet *)codeSet;
   CodeEntry *temp = myCodeSet->entry + code;
   CodeEntry *myEntry = temp;

   if (myEntry->allocate == 0) {
      myEntry->point = calloc(myEntry->size, sizeof(char));
   }
   block.data = myEntry->point;
   block.size = myEntry->size;
   
   for (i = myEntry->size - 1; i >= 0; i--) {
      block.data[i] = temp->data;
      temp = temp->prefix;

   }
   myEntry->allocate = 1;
   return block;
}





void FreeCode(void *codeSet, int code) {
   CodeSet *myCodeSet = (CodeSet *)codeSet;
   CodeEntry *myEntry = myCodeSet->entry + code;
   
   if (myEntry->allocate) {
      free(myEntry->point);
      myEntry->allocate = 0;
   }

}


void DestroyCodeSet(void *codeSet) {
   int i;
   CodeSet *myCodeSet = (CodeSet *)codeSet;
   CodeEntry *myEntry = myCodeSet->entry;
   
   for (i = 0; i < myCodeSet->numCodes; i++) {
      if (myEntry[i].allocate) {
         free(myEntry[i].point);
      }
   }
   free(myEntry);
   free(codeSet);
}
