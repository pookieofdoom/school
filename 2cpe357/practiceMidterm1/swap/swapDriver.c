#include<stdio.h>
#include"Midterm1.h"

int main() {
   double a, b;

   /* Scan in two numbers */
   scanf("%lf %lf", &a, &b);

   /* Run the swap function */
   swap(&a, &b);

   /* Print the results */
   printf("%.6f %.6f\n", a, b);

   return 0;
}
