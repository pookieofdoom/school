#include <stdio.h>
#include "puzzleLib.h"

int main()
{
   int myArray[PUZZLE_SIZE][PUZZLE_SIZE];
   int newArray[PUZZLE_SIZE][PUZZLE_SIZE];
   int fakeArray[PUZZLE_SIZE][PUZZLE_SIZE];
/*   int badArray[][PUZZLE_SIZE] = 
{1,2,3,4,5,5,6,7,0};*/
   int x, valid, solve;
   
   
   SetPuzzle(myArray, 1, 0);
   PrintPuzzle(myArray);
   SetPuzzleTo(myArray,newArray);
   PrintPuzzle(newArray);
   solve = IsSolved(myArray, 1, 0);
   printf("solved %d\n", solve);
   solve = IsSolved (myArray, 2, 0);
   printf("solved2 is 0 = %d\n", solve);
   solve = IsSolved(myArray, 1, 1);
   printf("snake is %d\n", solve);
   x = IsEqual(myArray, newArray);
   printf("%d\n", x);
   x = IsEqual(myArray, fakeArray);
   printf("%d\n", x);
   x = IsEqual (newArray, fakeArray);
   printf("%d\n", x);
   valid = IsValidPuzzle(myArray, 1);
   printf("%d\n", valid);
   valid = IsValidPuzzle(myArray, 2);
   printf("%d\n", valid);
   valid = IsValidPuzzle(fakeArray, 1);
   printf("%d\n", valid);
   

   
  /* SetPuzzle(myArray, 1, 1);
   PrintPuzzle(myArray);
   SetPuzzleTo(myArray,newArray);
   PrintPuzzle(newArray);
   x = IsEqual (newArray, fakeArray);
   printf("%d\n", x);
   x = IsEqual(myArray, fakeArray);
   printf("%d\n", x);
   x = IsEqual(myArray, newArray);
   printf("%d\n", x);
   */
   
   
   return 0;
}
  
