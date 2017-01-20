#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Midterm1.h"

int main() {
   int size, i;
   double *array;

   /* Read in the size of the array */
   scanf("%d", &size); 
  
   /* Dynamically allocate required memory */
   assert(NULL != (array = malloc(size * sizeof(double))));
   
   /* Populate array */
   for(i = 0; i < size; i++) {
      scanf("%lf", array + i);
   }

   /* Print the results */
   printf("%.6f\n", sum(array, size));

   return 0;
}
