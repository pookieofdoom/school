#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {                                                          
   int sum;                                                               
   double total;                                                          
   double square;                                                         
}State;                                                                   
                                                                          
                                                                          
void SumSquare(int vals, void *s) {                                       // Base: 4, Surcharge: 0
   ((State *)s)->square += pow(vals, 2);                                    // Base: 6, Surcharge: 0
}                                                                         
                                                                          
void PrintAverage(void *s) {                                              // Base: 3, Surcharge: 0
   printf("Average is %.2f\n", ((State*)s)->total / ((State *)s)->sum++); // Base: 10, Surcharge: 0
}                                                                         
                                                                          
void PrintSquare(void *s) {                                               // Base: 3, Surcharge: 0
   printf("Sum of Squares is: %.2f\n", ((State*)s)->square);              // Base: 6, Surcharge: 0
}                                                                         
                                                                          
void Average(int vals, void *s) {                                         // Base: 4, Surcharge: 0
   ((State *)s)->total += vals;                                           // Base: 4, Surcharge: 0
   ((State *)s)->sum++;                                                   // Base: 3, Surcharge: 0
}                                                                         

void ProcessInts(int numVals, int *vals, void (*statsComputer)(int, void *), void *state, void (*statsPrinter)(void *)) {
   int ndx;

   for (ndx = 0; ndx < numVals; ndx++) {
      statsComputer(vals[ndx], state);
   }   
   statsPrinter(state);
}

int main() {
   int count, ndx, *vals;
   double total = 0;
   
   State a = {total};
   scanf("%d", &count);

   vals = malloc(sizeof(int) * count);

   for (ndx = 0; ndx < count; ndx++) {
      scanf("%d", &vals[ndx]);
   }   
   ProcessInts(count, vals, SumSquare, &a, PrintAverage);
   ProcessInts(count, vals, Average, &a, PrintSquare);
   return 0;
}