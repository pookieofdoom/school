#include "Midterm1.h"
#include <stdio.h>
void las(int *array, int size, LASResult *result){
   int i;
   int saveIndex = -1;
   int temp = *array;
   int count = 0;
   int saveCount = 0;
   int saveIndex2 = -1;
   for(i=0; i<size-1; i++){
      if(i < size &&temp < *(array+1)){
         count++;
         if(count ==1)
            saveIndex = i;
      }
      
      else {
         if(count > saveCount){
            saveCount = count;
            saveIndex2 = saveIndex;
         }
         count = 0;
     }
      temp = *(array+1);
      array++;
     
   }
   
   
   if(count <saveCount){
      if(saveCount !=0){
         result->length = saveCount+1;
      }
      else
         result->length = saveCount;
      result->from = saveIndex2;
   }
   else {
       if(count !=0){
         result->length = count+1;
      }
      else
         result->length = count;
      
      result->from = saveIndex;
   }
}
