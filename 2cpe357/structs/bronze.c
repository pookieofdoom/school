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

int compare(Pair *p1, Pair *p2) {
   int ret = 1;
   if(p1->val1 < p2->val1 )
      ret = 0;
   if(p1->val1 == p2->val2)
      if(p1->val2 < p2->val2)
         ret = 0;
         
    return ret;
      

}




// Swap the contents of the first Pair with the second Pair

void swap(Pair *p1, Pair *p2) {
   Pair temp = *p1;
   *p1 = *p2;
   *p2 = temp;
   
   
}





void InsertSort(Pair vals[], int size) {
   Pair *next = vals + 1, *loc, *pLoc, *valsEnd = vals + size;

   while (next < valsEnd) {
      pLoc = next-1;
      loc = next++;
      
      //this pLoc >= vals is needed but somehow it works without it except on the website
      while(compare(pLoc, loc) && pLoc >= vals )
         swap(pLoc--, loc--);




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
