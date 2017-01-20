#include <stdio.h>


 double RunningAverage(double val) {
    static int count = 0;
    static double value = 0;
    value+=val;
    return value/++count;
   
}



int main() {
   double val;
   
   while (EOF != scanf("%lf", &val)) {
      printf("Running average %0.3f\n", RunningAverage(val));
   }
   return 0;
}