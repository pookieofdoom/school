#include <stdio.h>
#include <stdlib.h>
#include "problem1.h"

int main() {
   char stringA[100];
   char stringB[100];
   char *result;

   /* Read in two strings.
    * - Recall that scanf will skip any leading and/or trailing whitespace.
    */
   scanf("%s%s", stringA, stringB);

   /* Call the function being tested, print result, and free memory */
   result = prepend(stringA, stringB);
   printf("|%s|\n", result);
   free(result);

   /* Test prepending an empty string, print result, and free memory */
   result = prepend(stringA, ""); 
   printf("|%s|\n", result);
   free(result);

   /* Test prepending to an empty string, print result, and free memory */
   result = prepend("", stringB); 
   printf("|%s|\n", result);
   free(result);

   /* Test prepending to an empty string to an empty string... */
   result = prepend("", ""); 
   printf("|%s|\n", result);
   free(result);

   return 0;
}
