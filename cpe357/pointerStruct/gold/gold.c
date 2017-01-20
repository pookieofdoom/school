#include <stdio.h>

#define MAX 100

typedef struct {
   int first;
   int second;
   int third;
} TripleInts;

typedef struct {
   TripleInts *firstMax;
   TripleInts *secondMax;
   TripleInts *thirdMax;
} Stats;


void getStats(TripleInts *array, int size, Stats *stats) {
   stats->firstMax = stats->secondMax = stats->thirdMax = array++;
   int ndx;
   for(ndx=1; ndx<size; ndx++){
    
      if(stats->firstMax->first < array->first) 
        
         stats->firstMax = array;
       
 
      if(stats->secondMax->second < array->second)
        
         stats->secondMax = array;
        
 
      if(stats->thirdMax->third < array->third)
         
         stats->thirdMax = array;
         
    
      array++;
      
      
   }
   
  
}
void printStats(Stats *stats) {
     printf("firstMax: %d\n", stats->firstMax->first);
     printf("secondMax: %d\n", stats->secondMax->second);
     printf("thirdMax: %d\n", stats->thirdMax->third);
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