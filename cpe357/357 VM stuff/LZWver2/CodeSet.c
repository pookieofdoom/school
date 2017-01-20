#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "SmartAlloc.h"
#include "CodeSet.h"

typedef struct CodeEntry {
   char *point;
   unsigned short size;
   char data;
   struct CodeEntry *prefix;
   int allocate;
} CodeEntry;

typedef struct CodeSet {
   CodeEntry  *entry;
   int number;  
 }CodeSet;

void *CreateCodeSet(int numCodes) {
  
   void *codeset = malloc(sizeof(CodeSet));
   ((CodeSet *)codeset)->entry = malloc(sizeof(CodeEntry) * numCodes);
   ((CodeSet *)codeset)->number = 0;
  
   
   return codeset;
}

int NewCode(void *codeSet, char val) {
   
   //allocate data in additin to CodeSet and CodeEntry
   
  
   (((CodeSet *)codeSet)->entry+((CodeSet *)codeSet)->number)->size = 1;


   (((CodeSet*)codeSet)->entry+((CodeSet *)codeSet)->number)->data = val;

   ((CodeSet *)codeSet)->number += 1;
   //make entry point to null 
   (((CodeSet*)codeSet)->entry+((CodeSet *)codeSet)->number)->allocate = 0;
   return ((CodeSet *)codeSet)->number-1;
}

int ExtendCode(void *codeSet, int oldCode) {
   
     int index;

     index = ((CodeSet *)codeSet)->number;
    (((CodeSet *)codeSet)->entry+index)->size = (((CodeSet *)codeSet)->entry+oldCode)->size+1;
    
     
   /* for( i=0; i <(((CodeSet *)codeSet)->entry+oldCode)->size; i++) {
         (((CodeSet*)codeSet)->entry+index)->data[i] = (((CodeSet*)codeSet)->entry+oldCode)->data[i];
         
    }*/
     (((CodeSet *)codeSet)->entry+index)->prefix = ((CodeSet *)codeSet)->entry+oldCode;
    
     (((CodeSet*)codeSet)->entry+index)->data = 0;
  
     
     ((CodeSet *)codeSet)->number += 1;
     (((CodeSet *)codeSet)->entry+index)->allocate = 0;
 
   return index;
}

void SetSuffix(void *codeSet, int code, char suffix) {
  
  /* *((((CodeSet*)codeSet)->entry+code)->data +
   (((CodeSet*)codeSet)->entry+code)->size-1) = suffix ; */
   
   (((CodeSet*)codeSet)->entry+code)->data = suffix;
     
}


Code GetCode(void *codeSet, int code){
   Code block;
    (((CodeSet *)codeSet)->entry+code)->point =  malloc(sizeof(char) * (((CodeSet *)codeSet)->entry+code)->size);
   block.data = (((CodeSet *)codeSet)->entry+code)->point;
   int i;
  block.size = (((CodeSet *)codeSet)->entry+code)->size;
   CodeEntry *temp = (((CodeSet *)codeSet)->entry+code);
 
   
   for(i=(((CodeSet *)codeSet)->entry+code)->size-1; i >= 0  ; i--) {
    
     block.data[i] =  (temp->data);
  
      temp = temp->prefix;
    
   }

  // (((CodeSet *)codeSet)->entry+code)->point = block.data;
   
    (((CodeSet *)codeSet)->entry+code)->allocate = 1;
   
   return block;
}

/* Mark the code at index |code| as no longer needed, until a new
 * GetCode call is made for that code. */
void FreeCode(void *codeSet, int code) {

   if((((CodeSet *)codeSet)->entry+code)->allocate == 1){
     
      //free((((CodeSet *)codeSet)->entry+code)->point->data);
     
      free((((CodeSet *)codeSet)->entry+code)->point);
     
      //printf("point is %d \n", (((CodeSet *)codeSet)->entry+code)->point);
    (((CodeSet *)codeSet)->entry+code)->allocate = 0;
   
    
      
   }

   
}
   

void DestroyCodeSet(void *codeSet) {
   int i;
   //data, entry, codeSet
   for(i=0; i < ((CodeSet *)codeSet)->number; i++) {
      if(((CodeSet *)codeSet)->entry[i].allocate==1) {
      
         free(((CodeSet *)codeSet)->entry[i].point);
      }
      
   }
   
   free(((CodeSet *)codeSet)->entry);
   free(codeSet);
}
