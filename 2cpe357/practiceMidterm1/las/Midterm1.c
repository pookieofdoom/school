#include "Midterm1.h"
void las(int *array, int size, LASResult *result) {
   result->from = -1;
   result->length = 0;
   
   int count = 0;
   int i;
   int longestRun = 0;
   int saveIndex = -1;
   int saveIndex2 = -1;
   
   for(i=0; i<size; i++) {
      if(*(array+1) && (*array < *(array+1))) {
         
         count++;
         if(count == 1)
         {
            saveIndex = i;
         }
      }
      else{
         if(longestRun < count)
         {
            longestRun = count;
            saveIndex2 = saveIndex;
         }
         count = 0;
      }
      array++;
   
   
   }
   
   if(count >0 && longestRun == 0) {
      result->length = count;
      result->from = saveIndex;
   }
   else if(longestRun !=0){
      result->length = longestRun+1;
   result->from = saveIndex2;
   }
   
   
      
   
      
}