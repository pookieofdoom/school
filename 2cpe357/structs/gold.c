#include <stdio.h>

#define MAX 100

typedef struct {
   int valueA;
   int valueB;
   int valueC;
} TripleInts;

typedef struct {
   TripleInts *firstMax;
   TripleInts *secondMax;
   TripleInts *thirdMax;
} Stats;


void getStats(TripleInts *array, int size, Stats *stats) {
   stats->firstMax = stats->secondMax = stats->thirdMax = array++;
   int i;
   for(i=1; i < size; i ++) {
   
      if(stats->firstMax->valueA < array->valueA)
         stats->firstMax = array;
      if(stats->secondMax->valueB < array->valueB)
         stats->secondMax = array;
      if(stats->thirdMax->valueC < array->valueC)
         stats->thirdMax = array;
      
      array++;
 
   }
   

}

void printStats(Stats *stats) {
   printf("firstMax: %d\n", stats->firstMax->valueA);
   printf("secondMax: %d\n", stats->secondMax->valueB);
   printf("thirdMax: %d\n", stats->thirdMax->valueC);
}



int main() {
   TripleInts array[MAX];
   int ndx, size;
   Stats stats;

   scanf("%d", &size);
   for (ndx = 0; ndx < size; ndx++) {
      scanf("%d %d %d", &array[ndx].first, &array[ndx].second, &array[ndx].third);
   }

   getStats(array, size, &stats);

   printStats(&stats);

   return 0;
}