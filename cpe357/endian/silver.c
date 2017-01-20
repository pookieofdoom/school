#include <stdio.h>

#define BYTE 8
#define BYTE3 24

int main() {
   unsigned short s;
   int i;
   unsigned mask;

   scanf("%hx %x", &s, &i);

   mask = (1<<BYTE)-1 ; 
   printf("%X\n",mask);
   
   s= (s<<BYTE) |(s>>BYTE);
  
 //i =  i<<BYTE3 |  i>>BYTE3 & mask | (i & mask<<BYTE) <<BYTE | (i & mask<<BYTE*2)>>BYTE;

  //i = (i>>BYTE3-BYTE & mask) << BYTE;
 i = i>>BYTE & mask<<BYTE;


   printf("%X %X", s, i);


   return 0;
}
