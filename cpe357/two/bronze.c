#include <stdio.h>

int main() {
   int strange = 2147483648;
   
   if (strange != 0 && strange == -strange)
      printf("I am strange\n");
printf("sup\n");
printf("%d\n", strange );
   return 0;

}