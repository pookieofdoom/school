#include <stdio.h>

#define BYTE 8
#define BYTE3 24

int main() {
   unsigned short s;
   unsigned mask;

   scanf("%hx", &s);

   mask = s << BYTE ;
   s = mask | (s >> BYTE) & mask;
   printf("%X", s);

   return 0;
}
