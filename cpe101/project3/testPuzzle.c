#include <stdio.h>
#include <stdlib.h>
#include "puzzleLib.h"

#define UPPER_BOUND 99
#define TESTS 10

int reverse1DArray(int inArray[], int size);

int main()
{
  /* test puzzles (for PUZZLE_SIZE = 3) */
  int samplePuzzle[PUZZLE_SIZE][PUZZLE_SIZE]; 
  int samplePuzzle2[PUZZLE_SIZE][PUZZLE_SIZE];
 
  /* main puzzle */
  int puzzle[PUZZLE_SIZE][PUZZLE_SIZE];

  /* test sequence of moves */
  int sequence1[DEFAULT_N_MOVES];
  int sequence2[DEFAULT_N_MOVES];

  /* misc. variables */
  int row,column,index,value;
  int userInput = 0;
  int fail = 0;


  srandom(time(NULL));
  printf("Test Driver for the project 3 (sliding tile puzzles)\nFoaad Khosmood\nSize = %d\n\n",PUZZLE_SIZE);
  /* populate puzzle manually to all 1's */
  for (row=0;row < PUZZLE_SIZE; row++)
  {
     for (column=0;column < PUZZLE_SIZE; column++)
     {
        value = random() % (PUZZLE_SIZE*PUZZLE_SIZE);
        puzzle[row][column] = value;
        samplePuzzle[row][column] = value;
        samplePuzzle2[row][column] = 1;
     }
  }

  /* testing IsEqual */
  printf("Testing IsEqual: ");

  if(!IsEqual(samplePuzzle,samplePuzzle2))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("These 2 puzzles should not be equal, but IsEqual() returned 1:\n");
     PrintPuzzle(samplePuzzle2);
     printf("\n second one: \n");
     PrintPuzzle(samplePuzzle);
     fail = 1;
  }

  if(IsEqual(samplePuzzle2,samplePuzzle2))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("Yea, it's bad at this early point. I set two puzzles with these values:\n");
     PrintPuzzle(samplePuzzle2);
     printf("but IsEqual() didn't say they were the same... test it!\n");
     fail = 1;
  }

  if(IsEqual(puzzle,samplePuzzle))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("Yea, it's bad at this early point. I set two puzzles with these values:\n");
     PrintPuzzle(puzzle);
     printf("but IsEqual() didn't say they were the same (didn't return 1)... test it!\n");
     fail = 1;
  }

  puzzle[2][2] = 0;
  samplePuzzle[2][2] = 0;

  if(IsEqual(puzzle,samplePuzzle))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("Yea, it's bad at this early point. I set two puzzles with these values:\n");
     PrintPuzzle(puzzle);
     printf("but IsEqual() didn't say they were the same (didn't return 1)... test it!\n");
     fail = 1;
  }

  if (fail)
  {
     printf("I'm stopping here. Fix these errors and try again.\n");
     return 0;
  }
  
  printf("passed (1/8)\n");


  /* testing SetPuzzle */
  value = 1;
  for (row =0; row < PUZZLE_SIZE; row++)
      for (column=0; column < PUZZLE_SIZE; column++)
      {
          puzzle[row][column] = value;
          if (row % 2)
             samplePuzzle[row][PUZZLE_SIZE - 1 - column] = value;
          else
             samplePuzzle[row][column] = value;
          value++;
      }

  puzzle[PUZZLE_SIZE -1][PUZZLE_SIZE -1] = 0;
  if (!(PUZZLE_SIZE % 2))
	samplePuzzle[PUZZLE_SIZE - 1][0] = 0;
  else
        samplePuzzle[PUZZLE_SIZE - 1][PUZZLE_SIZE -1] = 0; 


  SetPuzzle(samplePuzzle2,1,0);
  printf("Testing SetPuzzle: ");
  if(IsEqual(puzzle,samplePuzzle2))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I used SetPuzzle(puzzle,1,0) and I got this: \n");
     PrintPuzzle(samplePuzzle2);
     printf("\n");
     PrintPuzzle(puzzle);
     fail = 1;
  }

  SetPuzzle(samplePuzzle2,1,1);
  if(IsEqual(samplePuzzle,samplePuzzle2))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I used SetPuzzle(puzzle,1,1) and I got this: \n");
     PrintPuzzle(samplePuzzle2);
     fail = 1;
  }

  value = random() % (PUZZLE_SIZE*PUZZLE_SIZE);
  for(row =0;row < PUZZLE_SIZE; row++)
     for(column = 0; column < PUZZLE_SIZE; column++)
     {
         if(puzzle[row][column])
            puzzle[row][column] += value;
         if(samplePuzzle[row][column])
            samplePuzzle[row][column] += value;
     }

  SetPuzzle(samplePuzzle2,value+1,0);
  if(IsEqual(puzzle,samplePuzzle2))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I tried SetPuzzle(puzzle,%d,0) didn't work.\n",value+1);
     fail = 1;
  }

  SetPuzzle(samplePuzzle2,value+1,1);
  if(IsEqual(samplePuzzle,samplePuzzle2))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I tried SetPuzzle(puzzle,%d,1) and... it wasn't pretty \n",value+1);
     fail = 1;
  }
  
  
  if (fail)
  {
     printf("I'm stopping here. Fix these errors and try again.\n");
     return 0;
  }

  printf("passed (2/8)\nTesting SetPuzzleTo: ");

  for(row = 0; row < PUZZLE_SIZE; row++)
     for(column = 0; column < PUZZLE_SIZE; column++)
         puzzle[row][column] = random() % PUZZLE_SIZE*PUZZLE_SIZE;
  

  SetPuzzleTo(puzzle,samplePuzzle);

  if(IsEqual(samplePuzzle,puzzle))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I tried SetPuzzleTo() to this puzzle and... it failed: \n");
     PrintPuzzle(puzzle);
     fail = 1;
  }

  value = random() % PUZZLE_SIZE * PUZZLE_SIZE;

  SetPuzzle(puzzle,value,0);
  SetPuzzleTo(puzzle,samplePuzzle);

  if(IsEqual(samplePuzzle,puzzle))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I tried SetPuzzleTo() to this puzzle and... it failed: \n");
     PrintPuzzle(puzzle);
     fail = 1;
  }

  value = random() % PUZZLE_SIZE * PUZZLE_SIZE;
  SetPuzzle(puzzle,value,1);
  SetPuzzleTo(puzzle,samplePuzzle);

  if(IsEqual(samplePuzzle,puzzle))
     printf(".");
  else
  {
     printf("FAILED!\n");
     printf("I tried SetPuzzleTo() to this puzzle and... it failed: \n");
     PrintPuzzle(puzzle);
     fail = 1;
  }

  if (fail)
  {
     printf("I'm stopping here. Fix these errors and try again.\n");
     return 0;
  }
    
  printf("passed (3/8)\nTesting IsValidPuzzle: ");


  value = 0;
  for (row =0; row < PUZZLE_SIZE; row++)
      for (column=0; column < PUZZLE_SIZE; column++)
      {
          samplePuzzle2[row][column] = 0;
          puzzle[row][column] = value;
          if (row % 2)
             samplePuzzle[row][PUZZLE_SIZE - 1 - column] = value;
          else
             samplePuzzle[row][column] = value;
          value++;
      }

  if(IsValidPuzzle(puzzle,1))
     printf(".");
  else
  {
     printf("This puzzle should be valid, but IsValidPuzzle() disagrees...\n");
     PrintPuzzle(puzzle);
     fail=1;
  }

  if(IsValidPuzzle(samplePuzzle,1))
     printf(".");
  else
  {
     printf("This puzzle should be valid, but IsValidPuzzle() disagrees...\n");
     PrintPuzzle(samplePuzzle);
     fail=1;
  }

  if(!IsValidPuzzle(samplePuzzle2,1))
     printf(".");
  else
  {
     printf("IsValidPuzzle() says this puzzle is valid, you belive this nonsens?\n");
     PrintPuzzle(samplePuzzle2);
     fail=1;
  }

 for(index=0;index < TESTS;index++)
 {
  value = 1+(random() % PUZZLE_SIZE);
  SetPuzzle(puzzle, value, index % 2);
  if(IsValidPuzzle(puzzle,value))
     printf(".");
  else
  {
     printf("This puzzle should be valid, but IsValidPuzzle() has other ideas...\n");
     PrintPuzzle(puzzle);
     fail = 1;
     break;
  }
 }

 for(index=0;index < TESTS;index++)
 {
  value = 1+(random() % PUZZLE_SIZE);
  SetPuzzle(puzzle, value, index % 2);
  puzzle[0][0] = 0;
  puzzle[1][1] = 0;
  if(!IsValidPuzzle(puzzle,value))
     printf(".");
  else
  {
     printf("FAIL!\nThis puzzle has too may zeros, but IsValidPuzzle just said it was fine! Gof figure...\n");
     PrintPuzzle(puzzle);
     fail = 1;
     break;
  }
 }


  if (fail)
  {
     printf("That's good for now: Fix these errors and try again.\n");
     return 0;
  }
  
  printf("passed (4/8)\nTesting IsSolved: ");

  for(index=0;index < TESTS;index++)
  {
     value = 1+(random() % PUZZLE_SIZE * PUZZLE_SIZE);
     userInput = random() % 2;
     SetPuzzle(puzzle, value, userInput);
     SetPuzzle(samplePuzzle, value, userInput);
     samplePuzzle[0][0] = 0;
     samplePuzzle[1][1] = 0;

  if(IsSolved(puzzle,value,userInput) && !IsSolved(samplePuzzle,value,userInput))
     printf(".");
  else
  {
     printf("FAILED!\nThis puzzle should be solved: \n");
     PrintPuzzle(puzzle);
     printf("and this one not solved:\n");
     PrintPuzzle(samplePuzzle);
     fail = 1;
     break;
  }
 }

  if (fail)
  {
     printf("Fix these errors and try again.\n");
     return 0;
  }

  printf("passed (5/8)\nTesting Move: ");

  value = 1 + random() % PUZZLE_SIZE;
  SetPuzzle(puzzle,value,1);

  if(Move(puzzle,0) || Move(puzzle,-1) || Move(puzzle,1) || Move(puzzle,2) ||
     Move(puzzle,value) || Move(puzzle,value+1) || Move(puzzle,value+2))
  {
     printf("FAILED!\nNo basic sanity checking in Move() function. \n");
     fail =1;
  }
  else
     printf(".");

  for (index = value+PUZZLE_SIZE*PUZZLE_SIZE -2; index >= value; index--)
     if (!(Move(puzzle,index)))
     {
        printf("FAILED!\n");
        printf("Tried to do the move (%d) in the following puzzle, but Move() returned invalid:\n",index);
        PrintPuzzle(puzzle);
        fail = 1;
     }
     else
        printf(".");

  SetPuzzle(puzzle,value,0);
  if(Move(puzzle,0) || Move(puzzle,-1) || Move(puzzle,1) || Move(puzzle,2) || 
     Move(puzzle,value) || Move(puzzle,value+1) || Move(puzzle,value+2) ||
     !Move(puzzle,value+PUZZLE_SIZE*PUZZLE_SIZE -2) ||
     !Move(puzzle,value+PUZZLE_SIZE*PUZZLE_SIZE -2))
  {
     printf("FAILED!\nMore basic sanity checking in Move() function failing. \n");
     fail =1;
  }
  else
     printf("..");

  if(fail)
  {
     printf("Take care of these and try again.\n");
     return 0;
  }
  printf("passed (6/8)\nTesting RandomMove: ");


  for (row=0; row <= 2; row++)
  {
  value = 1 + random() % PUZZLE_SIZE;
  SetPuzzle(puzzle,value,0);
  SetPuzzle(samplePuzzle,value,1);

  for (index=0; index < 2 * TESTS; index++)
  {
     userInput = RandomMove(puzzle);
     if (userInput && !IsValidPuzzle(puzzle,value) && !IsValidPuzzle(samplePuzzle,value))
     {
        printf("FAILED! \n");
        printf("just a made a move (%d) to both of these puzzles and it did not work:\n",userInput);
        PrintPuzzle(puzzle);
        printf("and...");
        PrintPuzzle(samplePuzzle);
        fail=1;
        break;
     }
     else
        printf(".");
  }
  }

  if(fail)
  {
     printf("Take care of these and try again.\n");
     return 0;
  }
  printf("passed (7/8)\nTesting MoveSequence: ");

  value = 1+random() % PUZZLE_SIZE; 
  SetPuzzle(puzzle,value,0);   		/* valid, solved puzzle */
  SetPuzzleTo(puzzle,samplePuzzle);     /* now copied into samplePuzzle */

  if (!IsSolved(puzzle,value,0) || !IsSolved(samplePuzzle,value,0) || !IsEqual(puzzle,samplePuzzle))
  {
     printf("FAILED SELF TESTS 4 -- exiting\n");
     fail = 1;
  }

  for (index=0;index<DEFAULT_N_MOVES;index++)
  {
     userInput = RandomMove(puzzle);
     if(userInput < 1 || !IsValidPuzzle(puzzle,value))
     {
        printf("Made a bad random move (%d) on this puzzle: \n",userInput);
        PrintPuzzle(puzzle);
        fail =1;
     }
     else
        sequence1[index] = userInput;
  }    
  
  SetPuzzle(puzzle,value,0);
  MoveSequence(puzzle,sequence1,DEFAULT_N_MOVES); /* make N moves on original puzzle */
  reverse1DArray(sequence1,DEFAULT_N_MOVES);      /* reverse the array */
  MoveSequence(puzzle,sequence1,DEFAULT_N_MOVES); /* make the N reverse moves */

  if (!IsSolved(puzzle,value,0) || !IsEqual(puzzle,samplePuzzle))
  {
     printf("FAILED!\nI tried to apply this sequence to this puzzle\nSequence = { ");
     for(index=0;index < DEFAULT_N_MOVES;index++)
         printf("%d ",sequence1[index]);

     printf("}\nPuzzle:");
     PrintPuzzle(samplePuzzle);
     fail = 1;
  }

  if(fail)
  {
     printf("Fix these and try again please");
     return 0;
  }
  else
     printf(".passed(8/8)\nSome extra tests: ");


  /* testing Shuffle (kind of a weak test: just sees if shuffling results in an invalid puzzle */
  userInput = ((int)random() % (UPPER_BOUND - PUZZLE_SIZE * PUZZLE_SIZE - 2));
  SetPuzzle(puzzle,userInput,1); /* new snake puzzle with random startNumber */

  for(index = 0; index < DEFAULT_N_MOVES; index++)
  {
     if(!IsValidPuzzle(puzzle,userInput) || !Shuffle(puzzle,DEFAULT_N_MOVES) || !IsValidPuzzle(puzzle,userInput))
     {
        printf("Failed! Shuffling resulted in a bad state... or something... \n");
        PrintPuzzle(puzzle);
        fail =1;
        return 0;
     }
     else
        printf(".");
  }

  /* testing RandomMove() */
  userInput = ((int)random() % (UPPER_BOUND - PUZZLE_SIZE * PUZZLE_SIZE - 2));
  SetPuzzle(puzzle,userInput,1); /* new snake puzzle with random startNumber */

  RandomMove(puzzle);
  SetPuzzleTo(puzzle,samplePuzzle);

  for (index =0; index < DEFAULT_N_MOVES; index++)
     sequence2[index] = RandomMove(puzzle);  /* sequence2 holds the random moves made */

  reverse1DArray(sequence2,DEFAULT_N_MOVES); /* reverse the array */
  MoveSequence(puzzle,sequence2,DEFAULT_N_MOVES); /* apply the reversed array moves */
  
  if (!IsEqual(puzzle,samplePuzzle))
  {
     printf("FAILED SELF TESTS -- exiting\n");
     return 0;
  }  
  else
     printf("passed!\n");

  printf("Congratulations you passed all these tests. But these are not comprehensive and you should do more. There will be other tests that we will use for the real assignment. Also, the GetUserMove() function and the driver part (the actual interactive puzzle in myPuzzle.c) has not been tested in this process.\n");

  return 0;
}


int reverse1DArray(int inArray[],int size)
{
  int index,temp;
  for (index = 0; index < size/2; index++)
  {
     temp = inArray[index];
     inArray[index] = inArray[size-index-1];
     inArray[size-index-1] = temp;
  }
  return 1;   
}
