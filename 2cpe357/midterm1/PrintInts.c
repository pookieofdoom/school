#include <stdio.h>
#include <stdlib.h>

int main() {
   int i, size, *vals;

   scanf("%d", &size);
   vals = malloc(sizeof(int) * size);
   
   for (i = 0; i < size; i++)
      scanf("%d", vals + i);

   for (i = 0; i < size; i++)
      printf("%d ", *vals++);

   return 0;
}
