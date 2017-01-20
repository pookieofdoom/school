#include <stdio.h>
#include "SmartAlloc.h"
#include "problem3.h"

/* Prototypes of funcitons used in main but not provided to student */
int* getArray(int size);
void cleanup(int *array);

int main() {
   int i, toSize, fromSize, at, actualSpace, expectSpace;
   int *to, *from, *result;

   /* Read in size of to-Array and allocate memory */
   scanf("%d", &toSize);
   to = getArray(toSize);

   /* Read in to-Array */
   for (i = 0; i < toSize; i++)
      scanf("%d", &to[i]);
   
   /* Read in size of from-Array and allocate memory */
   scanf("%d", &fromSize);
   from = getArray(fromSize);

   /* Read in from-Array */
   for (i = 0; i < fromSize; i++)
      scanf("%d", &from[i]);

   /* Read in index to insert at */
   scanf("%d", &at);

   /* Call funciton being tested */
   result = insertArray(to, toSize, at, from, fromSize);

   /* Print results */
   for (i = 0; i < toSize + fromSize - 1; i++)
      printf("%d, ", result[i]);

   if (toSize + fromSize)
      printf("%d\n", result[i]);

   /* Clean from array */
   cleanup(from);

   /* Check heap usage */
   /* MAKE SURE YOU included SmartAlloc.h AND after stdlib.h in your source. */
   actualSpace = report_space();
   expectSpace = (toSize + fromSize) * sizeof(int);

   if (actualSpace > expectSpace)
      printf("Too much memory used\n");
   else if (actualSpace < expectSpace)
      printf("Too little memory used\n");
   else
      printf("Expected amount of memory used\n");

   return 0;
}
