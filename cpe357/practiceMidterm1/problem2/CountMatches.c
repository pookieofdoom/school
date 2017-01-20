#include "Problem2.h"

int countMatches(void *vArr, int dim, void *vVal, int vBytes) {
   int count = 0;
   int i;
   
   if(sizeof(int) == vBytes){
      for(i=0; i <dim; i++) {
         
         if(*((int *)vArr) == *((int *)vVal))  {
            count++;
         }
         vArr+= vBytes;
      }
   
   
   }
   
     
     else if(sizeof(double) == vBytes && ((GPARecord *)vArr)->id  == 0 ){
     
         
         for(i=0; i <dim; i++) {
            
            if(*((double *)vArr) == *((double*)vVal))  {
               count++;
            }
            vArr+= vBytes;
         }
      }
    
    else {
    
      for(i=0; i <dim; i++) {
     
         if(((GPARecord *)vArr)->id == ((GPARecord *)vVal)->id && ((GPARecord *)vArr)->gpa == ((GPARecord *)vArr)->gpa )  {
            count++;
         }
         vArr+= vBytes;
      }
   
   }
   return count;
}


