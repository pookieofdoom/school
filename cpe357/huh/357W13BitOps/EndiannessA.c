#include <stdio.h>

#define BYTE 8

int main() {
   short s;
   unsigned i, mask;

   scanf("%hx %x", &s, &i);
   mask = 0xFF00;
   s = s << BYTE | s >> BYTE & mask >> BYTE;
   printf("%hX ", s);

   i = i << BYTE &(mask << BYTE*2 | mask) | i >> BYTE & (mask << BYTE | mask >> BYTE);

   printf("%8X", i << BYTE*2 | i >> BYTE*2 & (mask >> BYTE | mask));
}
