#include <stdio.h>
#include "Midterm1.h"

int main() {
   int a, b;

   /* Scan in two numbers */
   scanf("%d %d", &a, &b);

   /* Call the max function and print the results */
   printf("%d\n", max(&a, &b));

   return 0;
}
