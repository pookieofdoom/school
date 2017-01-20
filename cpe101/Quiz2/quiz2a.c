/*******************************************************************
 * Starter file for lab quiz 2
 * Name: Anthony Dinh
 * Section: 03
 * By submitting this file, I pledge to have done all my own work
 * and not received help from anyone other than my Instructor or TA
 */
#include <stdio.h>

int main()
{
   int count, cans1, cans2, cans3, x=0, y=0, z=0, i;
   char depart;
   printf("How many donations total? ");
   scanf("%d", &count);
   for (i=0; i<count; i++)
   {
      printf("What department? ");
      scanf(" %c", &depart);
   
      if(depart == 'c')
      {
         printf("How many cans? ");
         scanf("%d", &cans1);
         x = x + cans1;
      }
      if(depart == 'p')
      {
         printf("How many cans? ");
         scanf("%d", &cans2);
         y = y + cans2;
      }
      if(depart == 's')
      {
         printf("How many cans? ");
         scanf("%d", &cans3);
         z = z + cans3;
      }
   }
   printf("\nFinal count\n");
   printf("CSC: %3d\n", x);
   printf("CPE: %3d\n", y);
   printf("SE:  %3d\n", z);
   

   return 0;
}
