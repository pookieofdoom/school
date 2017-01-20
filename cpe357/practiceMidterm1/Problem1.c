#include <stdio.h>
#define SIZE 100


int main() {
   int arr[SIZE];
   int input;
   int count = 0;
   int i;
   int *temp = arr;
   int same = 0;
   int same2 = 0;
   int temp2;
   while( scanf("%d", &input) != EOF && input>0){
      arr[count] = input;
      
      count++;
   }
   
   i = count;
   count = 0;
   *temp = arr[count];   
   while(count <= i) {
      if(arr[count] == *temp)
         same++;
      else{
         if(same > same2) {
            same2 = same;
            temp2 = *temp;
         }
         temp += 1;
         count--;
         same = 0;
      }
      count++;
   }
   if(input<0)
      printf("Negative numbers are not allowed.\n");
   else
      printf("The longest chain was %d numbers long and the number was %d.\n", same2, temp2);  
   return 0;




}
