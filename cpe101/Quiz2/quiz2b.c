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
   int track1=0,track2=0,track3=0;
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
         if (track1 < cans1)
         {
            track1 = cans1;
         }
         x = x + cans1;
      }
      if(depart == 'p')
      {
         printf("How many cans? ");
         scanf("%d", &cans2);
         if (track2 < cans2)
         {
            track2 = cans2;
         }
         y = y + cans2;
      }
      if(depart == 's')
      {
         printf("How many cans? ");
         scanf("%d", &cans3);
         if (track3 < cans3)
         {
            track3 = cans3;
         }
         z = z + cans3;
      }
   }
   printf("\nFinal count\n");
   printf("CSC: %3d\n", x);
   printf("CPE: %3d\n", y);
   printf("SE:  %3d\n", z);
   
   if (track1 > track2 && track1 > track3)
   {
      printf("Largest Donation: %d\n", track1);
   }
   if (track2 > track1 && track2 > track3)
   {
      printf("Largest Donation: %d\n", track2);
   }
   if (track3 > track2 && track3 > track1)
   {
      printf("Largest Donation: %d\n", track3);
   }
   

   return 0;
}
