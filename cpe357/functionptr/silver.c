#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
   int sum;
   double total;
   double  square;

   
}State;


void sumsquare (int vals, void *s){
 
   ((State *)s)->square += sqrt(vals);
   printf("total is %d\n", ( (State *) s)->square );
}

void printAverage(void *s) {
   printf("Average is: %.2f\n", ((State*)s)->total / ( (State *) s)->sum++ );

}

void printSquare(void *s){
   printf("Sum of Squares is: %.2f\n", ((State*)s)->square);
}

void average (int vals, void *s) {
   ( (State *)s)->total += vals;
    
  ( (State *) s)->sum++  ;

}





void ProcessInts(int numVals, int *vals, void (*fp)(int, void *) , void *state, void (*printFunc)(void*) ) {
   int ndx;
   
   for (ndx = 0; ndx < numVals; ndx++) {
      fp(vals[ndx], state);
   }   

   printFunc(state);
}

int main() {
   double total = 0;
   
  State a  = {total};

   int count, ndx, *vals;

   scanf("%d", &count);

   vals = malloc(sizeof(int) * count);

   for(ndx = 0; ndx < count; ndx++) {
      scanf("%d", &vals[ndx]);
   }   

   ProcessInts(count, vals, average, &a, printAverage  );
   ProcessInts(count, vals, sumsquare, &a, printSquare );
    
   
   return 0;
}