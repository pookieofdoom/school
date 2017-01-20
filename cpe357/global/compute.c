#include <math.h>
#include "compute.h"

char *errorMessage;

int divide(int num, int denom, double *ret) {

   if(denom == 0) {
      errorMessage = "Can not divide by 0\n";
      return 1;
   }
   *ret = num / denom;
   return 0;
  
}



int squareRoot(int val, double *ret) {

   if(val <0) {
      errorMessage = "Can not take square root of a negative number\n";
      return 1;
   }
   *ret = sqrt(val);
   return 0;
}



int logBase10(int val, double *ret) {

   if(val <0) {
      errorMessage = "Can not take log of a negative number\n";
      return 1;
   
   }
   *ret = log10(val);
   return 0;

}