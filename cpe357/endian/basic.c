#include <stdio.h>

#define BYTE 8
#define BYTE3 24

int main() {
   unsigned short s;
   unsigned mask;

   scanf("%hx", &s);

   mask = s<<BYTE;
   printf("%X\n", mask);
   printf("%X\n", s>>BYTE);
   s= mask |(s>>BYTE);

   printf("%X", s);

   return 0;
}