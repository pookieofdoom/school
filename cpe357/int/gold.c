#include <stdio.h>

int Sum(int values, ...){
   
   int sum =0;
   int *holder = &values;
   while(*holder){
     sum += *holder++;

   }
return sum;

}



int main() {
   printf("%d\n", Sum(3,5,6,7,0));

   return 0;
}