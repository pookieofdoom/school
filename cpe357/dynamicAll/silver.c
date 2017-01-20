#include <stdio.h>
#include <stdlib.h>

int main() {
   int *p1, *p2, total = 0;
   
   p2 = malloc(sizeof(int));
   do {
      p1 = p2;
      p2 = malloc(sizeof(int));
      scanf("%d", p1); 
      total += *p1;
      free(p1);
   
   }while(total <20);
   free(p2);
   
   printf("total : %d\n", total);
   return 0;
}