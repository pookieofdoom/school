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
   int track1=0,track2=0,track3=0, a=0,b=0,c=0;
   char depart;
   int donate[100];
  
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
         donate[a] = cans1;
         a++;
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
         donate[b] = cans2;
         b++;
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
         donate[c] = cans3;
         c++;
         if (track3 < cans3)
         {
            track3 = cans3;
         }
         z = z + cans3;
      }
   }
   printf("\nFinal count\n");
   printf("CSC: %3d - ", x);
   for (i=0; i<a; i++)
   {
      printf("%d ", donate[a]);
   }
   printf("\nCPE: %3d - ", y);
   for (i=0; i < b; i++)
   {
      printf("%d ", donate[b]);
   }
   printf("\nSE:  %3d - ", z);
   for (i=0; i < c; i++)
   {
      printf("%d ", donate[c]);
   }
   
   if (track1 > track2 && track1 > track3)
   {
      printf("\nLargest Donation: %d\n", track1);
   }
   if (track2 > track1 && track2 > track3)
   {
      printf("\nLargest Donation: %d\n", track2);
   }
   if (track3 > track2 && track3 > track1)
   {
      printf("\nLargest Donation: %d\n", track3);
   }
   

   return 0;
}
