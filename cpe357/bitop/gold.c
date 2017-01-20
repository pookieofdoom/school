#include <stdio.h>

#define MASK 0xAAAAAAAA


int main() {
   int num;

   scanf("%x", &num);
   
   num =   (num & MASK)>>1  | (num & ~MASK) <<1;


   

   printf("%X\n", num);

   return 0;
}