#include <stdio.h>

#define NUMVALS 6
#define SIZE 5
#define MAX 31

int main() {
   int vals = 0;
   short curVal, idx = 0;
   while(idx < NUMVALS) {
      scanf("%hu", &curVal);
      vals |= curVal;
      printf("this is vals %d\n", vals);
      vals = vals << SIZE;
      idx++;
   }

   while(idx >0) {
      curVal = (vals >> (SIZE*idx)) & MAX;
      printf("%u ", curVal);
      idx--;
   }



   return 0;
}