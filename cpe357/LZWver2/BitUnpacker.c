/*
 * Copyright Software Innovations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BitUnpacker.h"
#define UINT_SIZE 32
#define UINT_MASK 0xFFFFFFFF




void buInit(BitUnpacker *unpacker) {
   unpacker->curData = 0;
   unpacker->nextData = 0;
   unpacker->bitsLeft = 0;
   unpacker->validNext = 0;
}



void buTakeData(BitUnpacker *unpacker, UInt set) {
   unpacker->nextData = set;
   unpacker->validNext = 1;
   
}

/*
 * return 1 on successful, 0 for needing next block
 */

 int unpack (BitUnpacker *unpacker, int size,  UInt *ret) {
   int end = 0 ; 
   
   //sets its curData to the next data if its valid
   if(unpacker->validNext) {
      unpacker->curData = unpacker->nextData;
      unpacker->validNext = 0;
      if(!unpacker->bitsLeft) {
         unpacker->bitsLeft = UINT_SIZE;
      }
      else {
    
      *ret =  (*ret >>UINT_SIZE - size) |(unpacker->curData >>UINT_SIZE - unpacker->bitsLeft) &~( UINT_MASK<<size);
      unpacker->bitsLeft = UINT_SIZE - unpacker->bitsLeft;
      
      end = 1;
         
      }
      
     
      
   }
    
   
   //actually upacking, then return 1
   if(unpacker->bitsLeft > 0 && end !=1) {

                        
         if(unpacker->bitsLeft == UINT_SIZE) {
            *ret = unpacker->curData >>unpacker->bitsLeft-size;
          }
         else if(unpacker->bitsLeft< UINT_SIZE) {
            *ret = (unpacker->curData >> unpacker->bitsLeft -size) &~( UINT_MASK<<size);
      }
         if(unpacker->bitsLeft < size) {
         
           *ret = (unpacker->curData << UINT_SIZE - unpacker->bitsLeft);
            unpacker->bitsLeft = size -unpacker->bitsLeft;
            end = 0;
        
         }   
     else {
      unpacker->bitsLeft -= size;
      end =  1;
      }
   }
  
   return end;
}




  
