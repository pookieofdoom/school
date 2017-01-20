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
   CodeSet *codeset = (CodeSet *)codeSet;
   CodeEntry *codeentry = codeset->entry+codeset->number++;
   codeentry->size = 1;
   codeentry->data = val;
   codeentry->allocate = 0;
   return codeset->number-1; 
}

int ExtendCode(void *codeSet, int oldCode) {
   
     int index;
     index = ((CodeSet *)codeSet)->number;
     CodeSet *codeset = (CodeSet *)codeSet;
     CodeEntry *codeentry =  codeset->entry+index;
    (((CodeSet *)codeSet)->entry+index)->size = (((CodeSet *)codeSet)->entry+oldCode)->size+1;
    
      

     (((CodeSet *)codeSet)->entry+index)->prefix = ((CodeSet *)codeSet)->entry+oldCode;
   

     (((CodeSet*)codeSet)->entry+index)->data = 0;
  
     
    
     (((CodeSet *)codeSet)->entry+index)->allocate = 0;
    
    ((CodeSet *)codeSet)->number += 1;
   
  
   return index;
}

void SetSuffix(void *codeSet, int code, char suffix) {
   
   if((((CodeSet *)codeSet)->entry+code)->allocate !=0)
      *((((CodeSet *)codeSet)->entry+code)->point+(((CodeSet *)codeSet)->entry+code)->size-1) = suffix;
   (((CodeSet*)codeSet)->entry+code)->data = suffix;
}


Code GetCode(void *codeSet, int code){

   int i;
 
   CodeEntry *temp = (((CodeSet *)codeSet)->entry+code);
   
   if((((CodeSet *)codeSet)->entry+code)->allocate ==0) {
      (((CodeSet *)codeSet)->entry+code)->point =  malloc(sizeof(char) * (((CodeSet *)codeSet)->entry+code)->size);
      
      }
    
      for(i=(((CodeSet *)codeSet)->entry+code)->size-1; i >= 0  ; i--) {
       
         if(temp->allocate >0 && i!=(((CodeSet *)codeSet)->entry+code)->size-1){
           
           
            memmove((((CodeSet *)codeSet)->entry+code)->point, temp->point, i+1);
            
          
            i = -1;
         }
         
         else{   
            
            (((CodeSet *)codeSet)->entry+code)->point[i] =  (temp->data); 
              
           temp = temp->prefix;
         }
    
      }

   
    (((CodeSet *)codeSet)->entry+code)->allocate++;
     
   
   return *(Code *)(((CodeSet *)codeSet)->entry+code);
}


void FreeCode(void *codeSet, int code) {
   
   (((CodeSet *)codeSet)->entry+code)->allocate--;
   if((((CodeSet *)codeSet)->entry+code)->allocate <=0){
     
   
    
      free((((CodeSet *)codeSet)->entry+code)->point);
     

    (((CodeSet *)codeSet)->entry+code)->allocate = 0;
   
    
      
   }

   
}
   

void DestroyCodeSet(void *codeSet) {
   int i;

   for(i=0; i < ((CodeSet *)codeSet)->number; i++) {
      if(((CodeSet *)codeSet)->entry[i].allocate>0) {
 
         free(((CodeSet *)codeSet)->entry[i].point);
      }
      
   }
   
   free(((CodeSet *)codeSet)->entry);
   free(codeSet);
}