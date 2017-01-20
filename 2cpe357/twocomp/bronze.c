#include <stdio.h>

int main() {
   int strange = 2147483647; //biggest value an int can hold + 1
   int i =0;
   for(i=0; i < 100; i++)  {
      printf("%d\n", strange++);
   }
   printf("%d\n", strange);
   if (strange != 0 && strange == -strange)
      printf("I am strange\n");
      
   return 0;
}