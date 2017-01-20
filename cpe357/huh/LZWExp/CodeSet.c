#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "SmartAlloc.h"
#include "CodeSet.h"

#define BLOCK_SIZE 4096

typedef struct MemBlock {
   char data[BLOCK_SIZE];
   int bytesUsed;
   struct MemBlock *next;
} MemBlock;

typedef struct CodeSet {
   Code *head;
   MemBlock *memBlock;
   int index;
   int size;
} CodeSet;

void *createCodeSet(int numCodes) {
   CodeSet *toReturn = malloc(sizeof(CodeSet));
   
   toReturn->head = malloc(sizeof(Code) * numCodes);
   toReturn->index = 0;
   toReturn->memBlock = NULL;
   toReturn->size = numCodes;
   return toReturn;
}

int newCode(void *codeSet, char val) {
   int toReturn = ((CodeSet*)codeSet)->index;
   MemBlock *new;
   Code *ptr;
   
   if (((CodeSet*)codeSet)->index < ((CodeSet*)codeSet)->size) {
      if (((CodeSet*)codeSet)->memBlock == NULL) {
         ((CodeSet*)codeSet)->memBlock = malloc(sizeof(MemBlock));
         ((CodeSet*)codeSet)->memBlock->bytesUsed = 0;
         ((CodeSet*)codeSet)->memBlock->next = NULL;
      }
      
      else if (((CodeSet*)codeSet)->memBlock->bytesUsed == BLOCK_SIZE ) {
         new = malloc(sizeof(MemBlock));
         new->bytesUsed = 0;
         new->next = ((CodeSet*)codeSet)->memBlock;
         ((CodeSet*)codeSet)->memBlock = new;
      }
      
      ((CodeSet*)codeSet)->memBlock->
       data[((CodeSet*)codeSet)->memBlock->bytesUsed] = val;
      ptr = ((CodeSet*)codeSet)->head;        
      ptr+= ((CodeSet*)codeSet)->index;
      ptr->data = &((CodeSet*)codeSet)->memBlock->
       data[((CodeSet*)codeSet)->memBlock->bytesUsed];
      ((CodeSet*)codeSet)->index++;
      ((CodeSet*)codeSet)->memBlock->bytesUsed += sizeof(val);
      ptr->size = sizeof(val);      
   }
   
   return toReturn;
}

int extendCode(void *codeSet, int oldCode) {
   Code old = getCode(codeSet, oldCode), *ptr;
   int toReturn = ((CodeSet*)codeSet)->index, count;
   MemBlock *new;
   
   if (((CodeSet*)codeSet)->index < ((CodeSet*)codeSet)->size) {
      if (((CodeSet*)codeSet)->memBlock->
       bytesUsed + (old.size)+1 > BLOCK_SIZE) {
         new = malloc(sizeof(MemBlock));
         new->bytesUsed = 0;
         new->next = ((CodeSet*)codeSet)->memBlock;
         ((CodeSet*)codeSet)->memBlock = new;
      }
      
      for (count = 0 ; count < old.size; count++) {
         ((CodeSet*)codeSet)->memBlock->
          data[((CodeSet*)codeSet)->memBlock->bytesUsed+count]
          = old.data[count];
      }
      
      ptr = ((CodeSet*)codeSet)->head;        
      ptr+= ((CodeSet*)codeSet)->index;
      ptr->data = &((CodeSet*)codeSet)->memBlock->
       data[((CodeSet*)codeSet)->memBlock->bytesUsed];
      ptr->data[old.size] = 0;
      ((CodeSet*)codeSet)->index++;
      ((CodeSet*)codeSet)->memBlock->bytesUsed += old.size + 1;
      ptr->size = old.size+1; 
   }
   
   return toReturn;
}

void setSuffix(void *codeSet, int code, char suffix) {
   Code *old = ((CodeSet*)codeSet)->head+code;
   int lastChar = old->size-1;
   
   old->data[lastChar] = suffix;
}

Code getCode(void *codeSet, int code) {
   Code *toReturn = ((CodeSet*)codeSet)->head+code;
   
   return *(toReturn);
}

void destroyCodeSet(void *codeSet) {
   MemBlock *temp;

   while (((CodeSet*)codeSet)->memBlock) {
      temp = ((CodeSet*)codeSet)->memBlock;
      ((CodeSet*)codeSet)->memBlock = temp->next;
      free(temp);
  }
  free(((CodeSet*)codeSet)->head);
  free(((CodeSet*)codeSet));
}
