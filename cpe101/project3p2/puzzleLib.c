/* Project 3
*
* Name: Anthony Dinh
* Instructor: Hatalsky
*/

#include <stdio.h>
#include <stdlib.h>
#include "puzzleLib.h"

/* this function is complete. Do not modify it */
void PrintPuzzle(int inPuzzle[PUZZLE_SIZE][PUZZLE_SIZE])
{
   int column,row;
   for (row=0;row < PUZZLE_SIZE;row++)
   {
      for(column=0;column < PUZZLE_SIZE;column++)
      {
         if (inPuzzle[row][column])
	 {
           printf("[ %2i ] ",inPuzzle[row][column]);
         }
         else /* this is for the empty tile which should contain 0 */
         { 
           printf("[    ] ");
         }
      }
      printf("\n\n");
   }
}

/* sets a puzzle in either regular or snake configuration */
/* this function is complete */
void SetPuzzle(int inPuzzle[][PUZZLE_SIZE], int startNum, int snake)
{
   int row, column;
   if(snake ==0)
   {
      for(row =0; row < PUZZLE_SIZE; row++)
      {
         for(column=0; column < PUZZLE_SIZE; column++)
         {
           
			if (row == PUZZLE_SIZE -1 && column == PUZZLE_SIZE -1)
			{
			   inPuzzle[row][column] = 0;
			}
			
            else
            {
               inPuzzle[row][column] = startNum++;
            }
         }		  
      }
   }

   else
   {
      for (row=0; row < PUZZLE_SIZE; row++)
      {
	     if (row%2 ==0)
		 {
            for(column=0; column < PUZZLE_SIZE; column++)
            {		       
			      if (row == PUZZLE_SIZE -1 && column == PUZZLE_SIZE -1)
			      {
			         inPuzzle[row][column] = 0;
			      }
           
			      else
                  { 
                     inPuzzle[row][column] = startNum++;
                  }			  
            }
         }
		 else
		 {
		    for (column = PUZZLE_SIZE-1; column >= 0; column--)
			{			   		       
			      if (row == PUZZLE_SIZE -1 && column == 0)
			      {
			         inPuzzle[row][column] = 0;
			      }
           
			      else
                  { 
                     inPuzzle[row][column] = startNum++;
                  }			                    
             }      
	   
          }
      }
   }
}



/* You need to add the rest of the functions below */
void SetPuzzleTo(int inPuzzle[][PUZZLE_SIZE], int outPuzzle[][PUZZLE_SIZE])
{
   int row, column;
   for (row =0; row <PUZZLE_SIZE; row++)
   {
      for(column =0; column < PUZZLE_SIZE; column++)
	  {
	     outPuzzle[row][column] = inPuzzle[row][column];
	  }
	}
}

int IsEqual(int puzzle1[][PUZZLE_SIZE], int puzzle2[][PUZZLE_SIZE])
{
   int row, column;
   for (row = 0; row < PUZZLE_SIZE; row++)
   {
      for(column=0; column < PUZZLE_SIZE; column++)
      {
         if(puzzle1[row][column] != puzzle2[row][column])
         {
            return 0;
         }
        
         
         
      }
   }
   return 1;
}
int IsValidPuzzle(int inPuzzle[][PUZZLE_SIZE],int startNum)
{
   int row, column, i, flag=0;
   for (row=0; row<PUZZLE_SIZE; row++)
   {
      for(column=0; column< PUZZLE_SIZE; column++)
      {
         if(inPuzzle[row][column] == 0)
         {
            flag =1;
            break;
         }
      }
   } 
   if( flag ==0)
   {
      return 0;
   }

   for(i = startNum; i <= (startNum + PUZZLE_SIZE * PUZZLE_SIZE 
- 2); i++)
   {
      flag = 0;
      for(row=0; row < PUZZLE_SIZE; row++)
      {
         for(column=0; column < PUZZLE_SIZE; column++)
         {
            if(inPuzzle[row][column] == i)
            {
               flag =1;
               break;
             }
          }
          if(flag)
          {
             break;
          }
       }
   if (flag ==0)
   {
      return 0;
   }
   }
   return 1;
}   



int IsSolved(int inPuzzle[][PUZZLE_SIZE], int startNum, int snake)
{
   int row, column;
   if (snake ==0)
   {
      for (row=0; row < PUZZLE_SIZE; row++)
      {
         for(column=0; column < PUZZLE_SIZE; column++)
         {
            
            if(row == PUZZLE_SIZE-1 && column == PUZZLE_SIZE -1 && inPuzzle[row][column] !=0)
            {
               return 0;
            }
            else if (inPuzzle[row][column] != startNum++ && row != PUZZLE_SIZE-1 && column != PUZZLE_SIZE -1)
            {
              
 	       return 0;
            }
            
         }
      }
   }
    else
    {
      for (row=0; row < PUZZLE_SIZE; row++)
      {
             if (row%2 ==0)
                 {
            for(column=0; column < PUZZLE_SIZE; column++)
            {
                              if (row == PUZZLE_SIZE -1 && column == PUZZLE_SIZE -1 && inPuzzle[row][column] !=0)
                              {
                                 return 0;
                              }

                              else if (inPuzzle[row][column] != startNum++ && row!= PUZZLE_SIZE-1 && column != PUZZLE_SIZE-1)
                  {
                     return 0;
                  }
            }
         }
                 else
                 {
                    for (column = PUZZLE_SIZE-1; column >= 0; column--)
                        {
                              if (row == PUZZLE_SIZE -1 && column == 0 && inPuzzle[row][column] !=0)
                              
                              {
                                 return 0;
                              }

                              else if (inPuzzle[row][column] != startNum++ && row!=PUZZLE_SIZE-1 && column !=0)
                  {
                     return 0;
                  }
             }

          }
      }
   }
      
   return 1;
}

int GetPlayerMove()
{
	int move;
	printf("Input your next move or -1 to exit ");
	scanf("%d", &move);
	return move;
}

int Move(int puzzle[][PUZZLE_SIZE], int tileNumber)
{
	int row, column;
	for (row=0; row <PUZZLE_SIZE; row++)
	{
		for(column=0; column < PUZZLE_SIZE; column++)
		{
			if(puzzle[row][column] == tileNumber)
			{
				/* TOP CORNERS */
				if (row ==0)
				{
					/*top left corner*/
					if (column ==0)
					{
						/*to the right*/
						if(puzzle[0][1] == 0)
						{
							puzzle[0][1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*directly below*/
						else if (puzzle[1][0] == 0)
						{
							puzzle[1][0] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
					/*top right corner*/
					else if (column == PUZZLE_SIZE -1)
					{
						/*to the left*/
						if( puzzle[0][PUZZLE_SIZE-2] == 0)
						{
							puzzle[0][PUZZLE_SIZE-2] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*directly below*/
						else if(puzzle[1][PUZZLE_SIZE -1] ==0)
						{
							puzzle[1][PUZZLE_SIZE-1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
					/*the rest of top row is edges*/
					else
					{
						/*to the right*/
						if (puzzle[0][column+1] == 0)
						{
							puzzle[0][column+1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*to the left*/
						else if (puzzle[0][column-1] == 0)
						{
							puzzle[0][column-1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/* below it*/
						else if (puzzle[1][column] == 0)
						{
							puzzle[1][column] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
				}
					
					/*bottom corners*/
				else if( row == PUZZLE_SIZE -1)
				{
					/*bottom left corner*/
					if (column == 0)
					{
						/* to the right*/
						if(puzzle[PUZZLE_SIZE-1][1] == 0)
						{
							puzzle[PUZZLE_SIZE-1][1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/* above it*/
						else if (puzzle[PUZZLE_SIZE-2][0] == 0)
						{
							puzzle[PUZZLE_SIZE-2][0] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
					/*bottom right corner*/
					else if (column == PUZZLE_SIZE-1)
					{
						/*to the left*/
						if (puzzle[PUZZLE_SIZE-1][PUZZLE_SIZE-2] == 0)
						{
							puzzle[PUZZLE_SIZE-1][PUZZLE_SIZE-2] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*above it*/
						else if (puzzle[PUZZLE_SIZE-2][PUZZLE_SIZE-1] ==0)
						{
							puzzle[PUZZLE_SIZE-2][PUZZLE_SIZE-1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
					/*the rest of bottom row is edges*/
					else
					{
						/*to the right*/
						if (puzzle[PUZZLE_SIZE-1][column+1] == 0)
						{
							puzzle[PUZZLE_SIZE-1][column+1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*to the left*/
						else if (puzzle[PUZZLE_SIZE-1][column-1] == 0)
						{
							puzzle[PUZZLE_SIZE-1][column-1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/* above it*/
						else if (puzzle[PUZZLE_SIZE-2][column] == 0)
						{
							puzzle[PUZZLE_SIZE-2][column] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
				}
				/*checking the first and last column for edges*/
				else if (column ==0)
				{
					if (row !=0 && row!= PUZZLE_SIZE-1)
					{
						/*right*/
						if(puzzle[row][1] == 0)
						{
							puzzle[row][1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*above*/
						else if(puzzle[row-1][0] == 0)
						{
							puzzle[row-1][0] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*below*/
						else if (puzzle[row+1][0] ==0)
						{
							puzzle[row+1][0] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
				}
				else if (column == PUZZLE_SIZE-1)
				{
					if( row!=0 && row != PUZZLE_SIZE-1)
					{
						/*left*/
						if(puzzle[row][PUZZLE_SIZE-2] ==0)
						{
							puzzle[row][PUZZLE_SIZE-2] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*above*/
						else if(puzzle[row-1][PUZZLE_SIZE-1] == 0)
						{
							puzzle[row-1][PUZZLE_SIZE-1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
						/*below*/
						else if (puzzle[row+1][PUZZLE_SIZE-1] ==0)
						{
							puzzle[row+1][PUZZLE_SIZE-1] = tileNumber;
							puzzle[row][column] = 0;
							return 1;
						}
					}
				}
				/*not corners or edres = neither!*/
				else
				{
					/*above*/
					if (puzzle[row-1][column] ==0)
					{
						puzzle[row-1][column] = tileNumber;
						puzzle[row][column] = 0;
						return 1;
					}
					/*below*/
					else if(puzzle[row+1][column] ==0)
					{
						puzzle[row+1][column] = tileNumber;
						puzzle[row][column] = 0;
						return 1;
					}
					/*left*/
					else if(puzzle[row][column-1] ==0)
					{
						puzzle[row][column-1] = tileNumber;
						puzzle[row][column] = 0;
						return 1;
					}
					/*right*/
					else if(puzzle[row][column+1] == 0)
					{
						puzzle[row][column+1] = tileNumber;
						puzzle[row][column] = 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int MoveSequence(int puzzle[][PUZZLE_SIZE], int movesArray[], int numberOfMoves)
{
	int copy[PUZZLE_SIZE][PUZZLE_SIZE];
	int i, x;
	SetPuzzleTo(puzzle, copy);
	
	for (i=0; i<numberOfMoves; i++)
	{
		x =Move(copy, movesArray[i]);
		if (x==0)
		{
			return 0;
		}
	}
	SetPuzzleTo(copy, puzzle);
	return 1;
}
int RandomMove(int puzzle[][PUZZLE_SIZE])
{
	int moves,row,column, counter, savetile;
	for (row=0; row<PUZZLE_SIZE; row++)
	{
		for(column=0; column < PUZZLE_SIZE; column ++)
		{
			if (puzzle[row][column] == 0)
			{
			/*ALL CORNERS*/
				if ((row ==0 || row == PUZZLE_SIZE-1) && (column ==0 || column == PUZZLE_SIZE-1))
				{
					moves = 2;
					
				}
				/*EDGES ON TOP AND BOTTOM ROW*/
				else if ((row ==0 || row == PUZZLE_SIZE-1) && (column !=0 || column != PUZZLE_SIZE-1))
				{
					moves = 3;
					
				}
				else if ((row!=0 || row != PUZZLE_SIZE-1) && (column ==0 || column == PUZZLE_SIZE-1))
				{
					moves = 3;
					
				}
				else
				{
					moves = 4;
					
				}
				break;
			}
		}
	}
	counter = ((int)random() % moves);
	for (row=0; row<PUZZLE_SIZE; row++)
	{
		for(column=0; column < PUZZLE_SIZE; column ++)
		{
			savetile = puzzle[row][column];
			if(Move(puzzle, savetile) == 1)
			{
				if (counter >0)
				{
					Move(puzzle,savetile);
					counter --;
				}
				else if (counter ==0)
				{
					return savetile;
				}
			}
		}
	}
	return 0;
}
			
	
	


int Shuffle(int puzzle[][PUZZLE_SIZE], int numberOfMoves)
{
	int i;
	for (i=0; i<numberOfMoves; i++)
	{
		if(!RandomMove(puzzle))
		{
			return 0;
		}
		
	}
	return 1;
}
						