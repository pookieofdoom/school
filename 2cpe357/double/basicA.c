#include <stdio.h>
#include <stdlib.h>

void setToNull(int **x) {
   *x = NULL;
}



int main() {
   int x = 10; 
   int *iPtr = &x; 

   setToNull(&iPtr);

   if (iPtr == NULL) {
      printf("Success!\n");
   }
   else {
      printf("Uh Oh.\n");
   }

   return 0;
}