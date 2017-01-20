#include <stdio.h>
#include <stdlib.h>

#define OFF1 4
#define OFF2 5

int main() {
   int *ptr = malloc(sizeof(int) * 10), temp;
   const int *ptr2 = malloc(sizeof(int));  // Can't change ptr2
   
   printf("Enter two integers: ");
   scanf("%d%d", ptr + OFF1, ptr + OFF2);
   free(ptr);
   free(ptr2);
   temp = ptr - ptr2;
   ptr = NULL;
   printf("Your integers were %d %d\n", ptr2[OFF1+temp], *(ptr2 + temp + OFF2));

   return 0;
}
