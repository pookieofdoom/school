#include <stdio.h>

#define BYTE 8
#define BYTE3 24

int main() {
   unsigned short s;
   int i;
   unsigned mask;

   scanf("%hx %x", &s, &i);

   mask = (1<<BYTE) - 1 ;
   

s= (s<<BYTE) |(s>>BYTE);
   printf("first set is %X\n", (i & mask << BYTE)<< BYTE);
   printf("second set is %X\n",i>>BYTE);

i =  i<<BYTE3 |  i>>BYTE3 & mask | (i & mask<<BYTE) <<BYTE | i>>BYTE & mask<<BYTE;

   printf("%X %X", s, i);

   return 0;
}
