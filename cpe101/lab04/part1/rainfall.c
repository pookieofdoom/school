/* Compute the sum of a list of rainfall measurements. */

#include <stdio.h>

#define SENTINEL -1	

int main(void)
{
   int rainfall;   /* input - current rainfall */
   int sum = 0;    /* output - sum of rainfalls input so far */
   int n = 0;
   double average;

   /* Accumulate sum of all rainfalls. */
   printf("Enter first rainfall (or a negative number to quit)> ");
   scanf("%d", &rainfall);   /* Get first rainfall. */
   while (rainfall >= 0)
   {
      sum = sum + rainfall;
      printf("Enter next rainfall (negative number to quit)> ");
      scanf("%d", &rainfall);   /* Get next rainfall. */
      n = n+1;
   }
   printf("\nSum of rainfall measurements is %d\n", sum);
   printf("Number of measurements is %d\n", n);
   average = (double)sum/n;
   if (average >= 0)
   {
      printf("Average rainfall is %.2f\n", average);
   }
   else
   {
      printf("There is no rainfall!\n");
   }

   return 0;
}
