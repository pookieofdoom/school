#include <stdio.h>
#include "SmartAlloc.h" // #include "SmartAlloc.h" if not on IHS
#include "CodeSet.h"

#define NUM_POINTERS 3

#define CHAR_PTR_SIZE 4
#define CODEENTRY_32BIT 40
#define CODEENTRY_64BIT 50
typedef struct CodeEntry {                                              
   unsigned char *point;                                                
   unsigned short size;                                                 
   unsigned char data;                                                  
   struct CodeEntry *prefix;   
   struct CodeEntry *next;
   struct CodeEntry *prev;
      
} CodeEntry;                                                            
                                                                        
typedef struct CodeSet {                                                
   CodeEntry *entry;                                                    
   int numCodes;
   CodeEntry *head;
   int cacheSize;                                                        
} CodeSet;                                                              
                                                                        
                                                                        
void *CreateCodeSet(int numCodes) {                                     // Base: 3, Surcharge: 0
   void *myCodeSet = calloc(1, sizeof(CodeSet));                        // Base: 7, Surcharge: 0
   ((CodeSet *)myCodeSet)->entry = calloc(numCodes, sizeof(CodeEntry)); // Base: 8, Surcharge: 0
   ((CodeSet *)myCodeSet)->numCodes = 0;                                // Base: 4, Surcharge: 0
   ((CodeSet *)myCodeSet)->head = calloc(1, sizeof(CodeEntry));
   ((CodeSet *)myCodeSet)->head->prev = ((CodeSet *)myCodeSet)->head;
   ((CodeSet *)myCodeSet)->head->next = ((CodeSet *)myCodeSet)->head;
   ((CodeSet *)myCodeSet)->cacheSize = 0;

   return myCodeSet;                                                    // Base: 1, Surcharge: 0
}                                                                       
                                                                        
                                                                        
int NewCode(void *codeSet, char val) {                                  // Base: 4, Surcharge: 0
   CodeSet *myCodeSet = (CodeSet *)codeSet;                             // Base: 4, Surcharge: 0
   CodeEntry *myEntry = myCodeSet->entry + myCodeSet->numCodes++;       // Base: 6, Surcharge: 0
   myEntry->size = 1;                                                   // Base: 3, Surcharge: 0
   myEntry->data = val;

   return myCodeSet->numCodes - 1;                                      // Base: 3, Surcharge: 0
                                                                        
}                                                                       
                                                                        
int ExtendCode(void *codeSet, int oldCode) {                            // Base: 4, Surcharge: 0
   CodeSet *myCodeSet = (CodeSet *)codeSet;                             // Base: 4, Surcharge: 0
   int index = myCodeSet->numCodes;                                     // Base: 3, Surcharge: 0
   CodeEntry *myEntry = myCodeSet->entry + index;                       // Base: 5, Surcharge: 0
   CodeEntry *oldEntry = myCodeSet->entry + oldCode;                    // Base: 5, Surcharge: 0

   myEntry->size = oldEntry->size + 1;                                  // Base: 5, Surcharge: 0
   myEntry->prefix = oldEntry;                                          // Base: 3, Surcharge: 0
   myEntry->data = 0;                                                   // Base: 3, Surcharge: 0
   myCodeSet->numCodes++;                                               // Base: 2, Surcharge: 0


   return index;                                                       // Base: 1, Surcharge: 0
                                                                        
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
   // set up a code to return and set all the values needed in here                                                  
   Code getCode;
   CodeSet *myCodeSet = (CodeSet *)codeSet;                             
   CodeEntry *myEntry = myCodeSet->entry + code; 
   //char *temp;

   getCode.size = myEntry->size;
   if (myEntry->point != NULL) {
      getCode.data = myEntry->point;
      if (myEntry->prev != NULL) {
         myEntry->next->prev = myEntry->prev;
         myEntry->prev->next = myEntry->next;
         myEntry->next = NULL;
         myEntry->prev = NULL;
         myCodeSet->cacheSize--;
      }
   }
   
   else if (myEntry->point == NULL) {
      //temp = calloc(myEntry->size, sizeof(char));
      //getCode.data = temp;
      //myEntry->point = temp;
      getCode.data = calloc(myEntry->size, sizeof(char));
      myEntry->point = getCode.data;
      while (myEntry != NULL && !*(getCode.data)) {
         if(myEntry->point && *myEntry->point) {
            memmove(getCode.data, myEntry->point, myEntry->size);
         }
         else{
            getCode.data[myEntry->size - 1] = myEntry->data;
         }
         myEntry = myEntry->prefix;
      }
   }
   

   return getCode;
}                                                                       
                                                                        
                                                                        
/* Mark the code at index |code| as no longer needed, until a new       
 * GetCode call is made for that code. */                               
                                                                        
void FreeCode(void *codeSet, int code) {                                
   CodeSet *myCodeSet = (CodeSet *)codeSet;                             
   CodeEntry *myEntry = myCodeSet->entry + code;    
   CodeEntry *temp = myCodeSet->head;
   
   if (myEntry->point != NULL) {

      if (myEntry->next != NULL && myEntry->prev != NULL) {
         myEntry->next->prev = myEntry->prev;
         myEntry->prev->next = myEntry->next;
         myCodeSet->cacheSize--;
      }
      //general adding
      myEntry->next = temp->next;
      myEntry->prev = temp;
      temp->next->prev = myEntry;
      temp->next = myEntry;
      myCodeSet->cacheSize++;

     
      //if size is too big, remove head and reconnect
      if (myCodeSet->cacheSize > LRU_SIZE) {

         myEntry = myCodeSet->head->prev;
         //now that im done with point i can free
         free(myEntry->point);
         myEntry->prev->next = myEntry->next;
         myEntry->next->prev = myEntry->prev;
         myEntry->next = NULL;
         myEntry->prev = NULL;
         myEntry->point = NULL;
         myCodeSet->cacheSize--;

      }           
                                                                        
   }                                                                    
                                                                        
}                                                                       
                                                                        
                                                                        
void DestroyCodeSet(void *codeSet) {                                                                                              
   CodeSet *myCodeSet = (CodeSet *)codeSet;                             
   CodeEntry *myEntry = myCodeSet->entry; 
   while (myCodeSet->numCodes) {
      if(myEntry->point) {
         free(myEntry->point);
      }
      //move down the entry
      myCodeSet->numCodes--;
      myEntry++;
   }                                                              
                                                                        
   free(myCodeSet->entry);
   free(myCodeSet->head);  
   free(codeSet);                                                       
}                                                                       