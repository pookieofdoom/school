#include <stdio.h>
void Swap(int *x, int *y) {
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

int main() {
   int x, y;

   scanf("%d", &x);
   scanf("%d", &y);

   printf("Before Swap: x = %d and y = %d\n", x, y);
   Swap(&x, &y);  
   printf("After Swap: x = %d and y = %d\n", x, y);

   return 0;
}

