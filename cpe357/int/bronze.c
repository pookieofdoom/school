#include <stdio.h>
#include <assert.h>

int main() {
   short s;
   char c;
   int value = 2147446362;
   
   if (value > 2100000000)
      printf("%d %d\n", s = value, c = value);

   return 0;
}
