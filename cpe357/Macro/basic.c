#include <stdio.h>

#define InRangeBound(x,y,z) ( (x) >(y) && (x) < (y) ? (x) : (x)  <(y) && (x) < (z) ? (y) : (x) > (y) && (x) > (z) ? (z) : (x))
//(5*5) > (2>1) && (5*5) < (7 &3) ? (5*5) : (7&3)) ;



int main() {
   printf("%d\n", InRangeBound(10, 0, 20));
   printf("%d\n", InRangeBound(-10, 0, 10));
   printf("%d\n", InRangeBound(5 * 5, 2 > 1, 7 & 3));
   printf("%d\n", InRangeBound(1 / 1 >> 0 << 0, 2 > 1, 7 & 3));
   printf("%d\n", InRangeBound(0 || 5 ? 6 : 2, 5 ^ 2, 256 | 127));
 
   return 0;
}