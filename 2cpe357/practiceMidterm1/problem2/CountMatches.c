#include "Problem2.h"

int countMatches(void *vArr, int dim, void *vVal, int vBytes) {
   
   int count = 0;
   int i;
   if(vBytes == sizeof(int)) {
      for(i=0; i< dim; i++) {
         if(*(int *)vArr == *(int *)vVal) {
            count++;
         }
         vArr += vBytes;
      }
   }
   else if (vBytes == sizeof(double)) {
      for(i=0; i< dim; i++) {
         if(*(double *)vArr == *(double *)vVal) {
            count++;
         }
         vArr += vBytes;
      }
   }
    else if (vBytes == sizeof(GPARecord)) {
      for(i=0; i< dim; i++) {
         if(((GPARecord *)vArr)->id == ((GPARecord *)vVal)->id && ((GPARecord *)vArr)->gpa == ((GPARecord *)vVal)->gpa) {
            count++;
         }
         vArr += vBytes;
      }
   }
      
   
      
   
   return count;
   
   
   
   
}