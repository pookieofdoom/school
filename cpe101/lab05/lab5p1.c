#include <stdio.h>
#define NUM_TEST_SCORES 35

int main()
{
   int score[NUM_TEST_SCORES], testNum = 1, i=0, count =0;
   
   
   printf("Enter test score %2d: ", testNum);
   scanf("%d", &score[i]);
   if( score[i] == -1)
   {
     count = 0;
   }   
   while(score[i] !=-1)
   {
      i++;
      testNum++;
      count++;
      printf("Enter test score %2d: ", testNum);
      scanf("%d", &score[i]);
      
   }
   
   printf("\nNumber of scores entered: %d\n", count);
   printf("Test scores entered     : ");
   
   
   for (i=0; i<testNum; i++)
   {  
      if (score[i] !=-1)
      {
         printf("%d ", score[i]);
      }
   }
   printf("\n");
   return 0;
}
