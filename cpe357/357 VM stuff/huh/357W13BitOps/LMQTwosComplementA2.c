#include <stdio.h>

nt main() {
   int strange = 2147483648;
   
   if (strange != 0 && strange == -strange)
      printf("I am strange\n");
}
