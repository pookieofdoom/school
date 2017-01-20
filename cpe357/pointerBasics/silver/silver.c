#include <stdio.h>

int main() {
   int i1 = 10, i2 = 20, i3 = 30, *iPtr1 = &i1, *iPtr2 = &i2, *iPtr3;
    iPtr3 = iPtr2;
    iPtr2 = iPtr1;
    iPtr1 = iPtr3;
    printf("%d %d %d %d %d %d\n", i1, i2, i3, *iPtr1, *iPtr2, *iPtr3);

   return 0;
}