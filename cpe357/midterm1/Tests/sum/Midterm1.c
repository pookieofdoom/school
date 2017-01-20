#include "Midterm1.h"

double sum(double *array, int size){
   int i;
   double sum =0;
   for(i=0; i<size; i++){
      sum = sum + *array;
      array++;
   }
   return sum;
}
