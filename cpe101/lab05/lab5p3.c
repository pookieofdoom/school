#include <stdio.h>
#define NUM_TEST_SCORES 35

double average (int score[], int count); 
int findIndex (int score[], int count, int value); 

int main()
{
   int score[NUM_TEST_SCORES], testNum = 1, i=0, count =0;
   int value, index;
   double avg;
   
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
   printf("Enter test score to search for: ");
   scanf("%d", &value);
   printf("\nNumber of scores entered: %d\n", count);
   printf("Test scores entered     : ");
   
   
   for (i=0; i<testNum; i++)
   {  
      if (score[i] !=-1)
      {
         printf("%d ", score[i]);
      }
   }
   if (score[i] !=-1)
   {
      avg = average (score,count);
      printf("\nAverage test score      : %.1f\n", avg);
   }  
   
   index = findIndex (score, count, value);
   if (index != -1)
   {
      printf("The score %d first occurs at index %d.\n", value, index);
   }
   else
   {
      printf("The score %d does not occur in the array.\n", value);
   }
   
   return 0;
}

double average (int score[], int count)
{
   double sum =0, avg;
   int i;
   for (i=0; i < count; i++)
   {
      if (score[i] != -1)
      {
         sum = sum + score[i];
      }
   }
   avg = (double)(sum/count);
   return avg;
}

int findIndex (int score[], int count, int value)
{
   int i=0;
   while (i < count)
   {
      if(score[i] == value)
      {
         return i;
      }
	i++; 
     
   }
   return -1;
}   
         
