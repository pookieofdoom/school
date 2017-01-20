#include <stdio.h>

#define MAX 100

// One pair is "less" than another if either its val1 is less than the other's val1, or if
// val1's are tied, then if its val2 is less than the other's val2.
typedef struct {
   int val1;
   int val2;
} Pair;

// Takes in two Pairs and returns 1 if the first Pair is "greater" than the second Pair. 
// else it returns 0

int Compare(Pair *one, Pair *two) {
   int temp = 0;
   if(one->val1 > two->val1)
      temp = 1;
   if(one-> val1 == two-> val1) {
      if(one->val2 > two-> val2) {
         temp = 1;
      }
   }
   return temp;
}

void Swap(Pair *one, Pair *two) {
   Pair temp = *one;
   *one = *two;
   *two = temp;
  
   
   
}

void InsertSort(Pair vals[], int size) {
   Pair *next = vals + 1, *loc, *pLoc, *valsEnd = vals + size;

   while (next < valsEnd) {
      pLoc = next-1;
      loc = next++;
      printf("this is compare: %d\n",Compare(pLoc,loc));
      printf("this is loc's points (%d,%d)\n", loc->val1, loc->val2);
      printf("this is pLoc's points (%d,%d)\n", pLoc->val1, pLoc->val2);
      printf("this is next points (%d,%d)\n", next->val1, next->val2); 
      while(Compare(pLoc, loc) && vals <= pLoc) {
         Swap(pLoc--, loc--);
      }
	  
      
      
         
   }
}
int main() {
   Pair vals[MAX];
   int numVals, ndx;

   scanf("%d", &numVals);
   for (ndx = 0; ndx < numVals; ndx++)
      scanf("%d %d", &vals[ndx].val1, &vals[ndx].val2);

   InsertSort(vals, numVals);

   for (ndx = 0; ndx < numVals; ndx++)
      printf("(%d, %d) ", vals[ndx].val1, vals[ndx].val2);
   printf("\n");

   return 0;
}