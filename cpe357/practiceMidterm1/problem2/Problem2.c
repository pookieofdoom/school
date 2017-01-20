#include "Problem2.h"

#define IDIM 6
#define DDIM 5
#define SDIM 3


/*
You are provided with a `main()` function that creates some arrays of
integers, doubles, and structs. You must write a function `countMatches`
which searches for a given element within that array and returns the number
of times that particular element is found withing the array.

`countMatches` takes four parameters: `void *arr, int dim, void *val, int vBytes`
 * `void *arr`: The array in which to search
 * `int dim`: The number of elements in the array
 * `void *val`: The value to search for
 * `int vBytes`: The number of bytes in `val`, and in each element in `arr`
 */
int main() {
   int ndx, iVal = 42, iArr[] = {1, 2, 3, 42, 4, 42};
   double dVal = 3.1415, dArr[] = {3, 5, 7, 9, 11};
   GPARecord sVal = {42, 4.2}, sArr[] = {{21, 2.1}, {19, 3.7}, {42, 4.2}};

   printf("iArr %d\n", countMatches(iArr, IDIM, &iVal, sizeof(int)));
   printf("dArr %d\n", countMatches(dArr, DDIM, &dVal, sizeof(double)));
   printf("sArr %d\n", countMatches(sArr, SDIM, &sVal, sizeof(GPARecord)));

   return 0;
}
