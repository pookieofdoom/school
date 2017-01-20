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
   struct CodeEntry *next;
   struct CodeEntry *prev;
   int allocate;

} CodeEntry;

typedef struct CodeSet {
   CodeEntry  *entry;
   int number;  
   CodeEntry *head;
   int cachesize;
 }CodeSet;

void *CreateCodeSet(int numCodes) {
  
   void *codeset = malloc(sizeof(CodeSet));
   ((CodeSet *)codeset)->entry = malloc(sizeof(CodeEntry) * numCodes);
   ((CodeSet *)codeset)->number = 0;
   ((CodeSet *)codeset)->head=NULL;
   ((CodeSet *)codeset)->cachesize = 0;
   
   
   return codeset;
}

int NewCode(void *codeSet, char val) {
   CodeSet *codeset = (CodeSet *)codeSet;
   CodeEntry *codeentry = codeset->entry+codeset->number++;
   codeentry->size = 1;
   codeentry->data = val;
   codeentry->allocate = 0;
   //codeset->head = NULL;
   codeentry->next = NULL;
  
      codeentry->prev = NULL;
      //codeset->cachesize = 0;
   return codeset->number-1; 
}

int ExtendCode(void *codeSet, int oldCode) {
   CodeSet *codeset = (CodeSet *)codeSet;
   int index = codeset->number;
   CodeEntry *codeentry =  codeset->entry+index;
   CodeEntry *oldentry = codeset->entry+oldCode;
   codeentry->size = oldentry->size+1;
   codeentry->prefix = oldentry;
   codeentry->data = 0;
   codeentry->allocate = 0;
   codeset->number++;
   //codeset->head = NULL;
   codeentry->next = NULL;
  
      codeentry->prev = NULL;
  // codeset->cachesize = 0;
   return index;
}

void SetSuffix(void *codeSet, int code, char suffix) {
   CodeSet *codeset =(CodeSet *)codeSet;
   CodeEntry *codeentry = codeset->entry+code;
   if(codeentry->allocate) {
      codeentry->point[codeentry->size-1] = suffix;
   }
   codeentry->data = suffix;
}


Code GetCode(void *codeSet, int code){
   int i;
   CodeSet *codeset = (CodeSet *)codeSet;
   CodeEntry *temp = codeset->entry+code;
   CodeEntry *codeentry = temp;
   
   if(codeentry->next !=NULL && codeentry->prev != NULL ) {
   
      if(codeentry->next != codeentry && codeentry->prev != codeentry && codeentry->allocate ==0) {
         codeentry->prev->next = codeentry->next;
     
         codeentry->next->prev = codeentry->prev;
      }
      else {
         
         
         codeset->head = NULL;
      }
      
      codeentry->next = NULL;
  
      codeentry->prev = NULL;
      
      codeset->cachesize--;
     
      
   }
   
  
   else if(codeentry->allocate ==0) {
     
      codeentry->point =  malloc(sizeof(char) * codeentry->size);
      
   }
    
    for(i=codeentry->size; i > 0  ; i--) {
       
      if(temp->allocate){
         memmove(codeentry->point, temp->point, i);
         i = 0;
      }
         
      else{   
         codeentry->point[i-1] =  temp->data; 
         temp = temp->prefix;
      }
    
   }
  codeentry->allocate++;
   
   return *(Code *)codeentry;
}



void FreeCode(void *codeSet, int code) {
   CodeSet *codeset = (CodeSet *)codeSet;
   CodeEntry *codeentry = codeset->entry+code;
  
  
   
   if(--codeentry->allocate <=0){
      //empty cache
       
      if(codeset->head ==NULL) {
       
         codeset->head = codeentry;
         codeset->head->prev = codeset->head;
         codeset->head->next = codeset->head;
         codeset->cachesize++;
         
      }
      //general adding
      else if(codeentry->next ==NULL && codeentry->prev ==NULL){
      
         codeentry->prev = codeset->head->prev;
         codeentry->next = codeset->head;
         codeset->head->prev->next = codeentry;
         codeset->head->prev = codeentry;
         codeset->cachesize++;
      
      }
      //if the size is too big remove the head and reconnect
      if(codeset->cachesize > LRU_SIZE) {
     
         free(codeset->head->point);
         codeset->head->prev->next = codeset->head->next;
         codeset->head->next->prev = codeset->head->prev;
         codeset->head = codeset->head->next;
         codeset->cachesize--;
         
       
         
      
      }
     
   }
  
}
   

void DestroyCodeSet(void *codeSet) {
   int i;
   CodeSet *codeset = (CodeSet *)codeSet;
   CodeEntry *codeentry = codeset->entry;
   CodeEntry *temp = codeset->head;
   
   for(i=0; i < codeset->number; i++) {
  
  
       
      if(codeentry[i].allocate) {
         
         free(codeentry[i].point);
      }
      
   }

  for(i=0; i<codeset->cachesize;i++) {
    
      
      
      free(temp->point);
    
      temp = temp->next;
      
   }
   free(codeentry);
   free(codeSet);
   
   
}