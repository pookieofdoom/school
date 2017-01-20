#include <limits.h>
#include <stdio.h>

int main() {
   short s1 = SHRT_MAX, s2 = SHRT_MIN;

   s1 = -s1;
   s2 = SHRT_MAX;

   



   printf("%d %d", s1, s2);   

   return 0;
}