#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Midterm1.h"

int main() {
   int size, i;
   int *array;
   LASResult result = {-99, -99};

   /* Read in the size of the array */
   scanf("%d", &size); 

   /* Dynamically allocate required memory */
   assert(NULL != ( array = malloc(size * sizeof(int))));

   /* Populate array */
   for(i = 0; i < size; i++) {
      scanf("%d", array + i);
   }

   /* Call the las function */
   las(array, size, &result);

   /* Print the results */
   printf("%d %d\n", result.from, result.length);

   return 0;
}
