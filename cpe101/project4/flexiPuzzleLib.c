/* flexiPuzzle library header file 
 * the struct version
 * Foaad Khosmood / Spring 2013 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flexiPuzzleLib.h"

/* prints just the name of the inPuzzle */
void PrintName(flexiPuzzle inPuzzle)
{
   int index;
   int length = strlen(inPuzzle.name);
   int problemFlag = 0;

   if (length < 1 || length > MAX_NAME_LENGTH-1)
   {
      problemFlag = 1;
   }

   for (index=0; index < length; index++)
   {
      if (!isalpha(inPuzzle.name[index]) && inPuzzle.name[index] != ' ')
      {
          problemFlag = 1;
          break;
      }
   }

   if(problemFlag)
   {
      printf("UNKNOWN");
   }
   else
   {
      printf("%s",inPuzzle.name);
   }
}

/* returns the true size from inPuzzle */
int GetSize(flexiPuzzle inPuzzle)
{
    return inPuzzle.size;
}

/* return inPuzzle's start number by reading it from the structure */
int GetStartNum(flexiPuzzle inPuzzle)
{
    return inPuzzle.startNum;
}

/* return inPuzzle's snake attribute (0 for regular, 1 for snake configuration) */
int GetSnakeStatus(flexiPuzzle inPuzzle)
{
    return inPuzzle.snake;
}

/* return inPuzzle's distanceToSolution */
double GetDistanceToSolution(flexiPuzzle inPuzzle)
{
    return inPuzzle.distanceToSolution;
}

void PrintPuzzle(flexiPuzzle inPuzzle) /* print a given puzzle */
{
   int row, column, currentSize;

   printf("name: ");
   PrintName(inPuzzle);
   printf(" | configuration: ");
   if(GetSnakeStatus(inPuzzle))
   {
       printf("snake");
   }
   else
   {
       printf("regular");
   }

   currentSize = GetSize(inPuzzle);

   printf("\nsize: %d | start number: %d | solved? ",currentSize, GetStartNum(inPuzzle));
   if(inPuzzle.solved)
   {
       printf("Yes");
   }
   else
   {
       printf("No | distance: %.3f",GetDistanceToSolution(inPuzzle));
   }
   printf("\n--------------------------------------------------------\n");

   for (row = 0; row < currentSize; row ++)
   {
       for (column = 0; column < currentSize; column++)
       {
           if(inPuzzle.tiles[row][column])
           {
               printf("[ %2i ] ",inPuzzle.tiles[row][column]);
           }
           else
           {
               printf("[    ] ");
           }
       }
       printf("\n\n");
   }       
} /* end of PrintPuzzle */

flexiPuzzle SetPuzzleName(flexiPuzzle inPuzzle,char name[])
{
	if(strlen(name) > MAX_NAME_LENGTH)
	{
		strncpy(inPuzzle.name, name, MAX_NAME_LENGTH);
	}
	else
	{
		strcpy(inPuzzle.name, name);
	}
	return inPuzzle;
}


flexiPuzzle SetPuzzle(char name[], int size, int startNum, int snake)
{
	flexiPuzzle inPuzzle;
   int row, column;
	inPuzzle = SetPuzzleName(inPuzzle, name);
	inPuzzle.snake = snake;
	inPuzzle.solved = 1;
	inPuzzle.startNum = startNum;
	inPuzzle.moves[0] = -2;
	inPuzzle.distanceToSolution = 0.0;
	inPuzzle.size = size;
   if(snake ==0)
   {
      for(row =0; row < inPuzzle.size; row++)
      {
         for(column=0; column < inPuzzle.size; column++)
         {
           
			if (row == inPuzzle.size -1 && column == inPuzzle.size -1)
			{
			   inPuzzle.tiles[row][column] = 0;
			}
			
            else
            {
               inPuzzle.tiles[row][column] = startNum++;
            }
         }		  
      }
   }

   else
   {
      for (row=0; row < inPuzzle.size; row++)
      {
	     if (row%2 ==0)
	
		 {
            for(column=0; column < inPuzzle.size; column++)
            {		       
			      if (row == inPuzzle.size -1 && column == inPuzzle.size -1)
			      {
			         inPuzzle.tiles[row][column] = 0;
			      }
           
			      else
                  { 
                     inPuzzle.tiles[row][column] = startNum++;
                  }			  
            }
         }
		 else
		 {
		    for (column = inPuzzle.size-1; column >= 0; column--)
			{			   		       
			      if (row == inPuzzle.size -1 && column == 0)
			      {
			         inPuzzle.tiles[row][column] = 0;
			      }
           
			      else
                  { 
                     inPuzzle.tiles[row][column] = startNum++;
                  }			                    
             }      
	   
          }
      }
   }
   return inPuzzle;
}

flexiPuzzle SetSolvedState(flexiPuzzle inPuzzle, int solved)
{
	inPuzzle.solved = solved;
	return inPuzzle;
}

flexiPuzzle SetPuzzleTo(flexiPuzzle inPuzzle)
{
	int row, column, move;
	flexiPuzzle outPuzzle;
	SetPuzzleName(outPuzzle, inPuzzle.name);
	outPuzzle.size = inPuzzle.size;
	outPuzzle.startNum = inPuzzle.startNum;
	outPuzzle.snake = inPuzzle.snake;
	outPuzzle.solved = inPuzzle.solved;
	outPuzzle.distanceToSolution = inPuzzle.distanceToSolution;
	
   for (row =0; row <inPuzzle.size; row++)
   {
      for(column =0; column < inPuzzle.size; column++)
	  {
	     outPuzzle.tiles[row][column] = inPuzzle.tiles[row][column];
	  }
	}
	for(move=0; move < MOVE_HISTORY_SIZE +1; move++)
	{
		outPuzzle.moves[move] = inPuzzle.moves[move];
	}
	return outPuzzle;
}

tilePosition GetPosition(flexiPuzzle inPuzzle, int tileNumber)
{
   tilePosition position;
	int row, column;
	for (row=0; row<inPuzzle.size; row++)
	{
		for(column=0; column < inPuzzle.size; column++)
		{
			if (inPuzzle.tiles[row][column] == tileNumber)
			{
				position.row = row;
				position.column = column;
			}
		}
	}
	return position;
}


int IsSamePosition(tilePosition position1, tilePosition position2)
{
	if (position1.row == position2.row && position1.column == position2.column)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int ManhattanDistance(tilePosition position1, tilePosition position2)
{
	int disrow, discol;
	disrow = position1.row - position2.row;
	if (disrow < 0)
	{
		disrow = disrow * -1;
	}
	discol = position1.column - position2.column;
	if (discol < 0)
	{
		discol = discol * -1;
	}
	return disrow + discol;
}


int IsSameState(flexiPuzzle puzzle1, flexiPuzzle puzzle2)
{
	int row, column;
	if(puzzle1.size != puzzle2.size || puzzle1.startNum != puzzle2.startNum || puzzle1.snake != puzzle2.snake)
	{
		return 0;
	}
	for(row=0; row <puzzle1.size; row++)
	{
		for(column=0; column < puzzle1.size; column++)
		{
			if (puzzle1.tiles[row][column] != puzzle2.tiles[row][column])
			{
				return 0;
			}
		}
	}
	return 1;
				
}


int IsIdentical(flexiPuzzle puzzle1, flexiPuzzle puzzle2)
{
	int move;
	if (IsSameState(puzzle1,puzzle2) == 0)
	{
		return 0;
	}
	if(strcmp(puzzle1.name,puzzle2.name) > 0)
	{
		return 0;
	}
	for(move=0; move < MOVE_HISTORY_SIZE +1; move++)
	{
		if (puzzle1.moves[move] != puzzle2.moves[move])
		{
			return 0;
		}
	}
	if (puzzle1.solved != puzzle2.solved || puzzle1.distanceToSolution != puzzle2.distanceToSolution)
	{
		return 0;
	}
	return 1;

}

int IsValidPuzzle(flexiPuzzle inPuzzle)
{
   int row, column, i, flag=0;
   for (row=0; row< inPuzzle.size; row++)
   {
      for(column=0; column< inPuzzle.size; column++)
      {
         if(inPuzzle.tiles[row][column] == 0)
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

   for(i = inPuzzle.startNum; i <= (inPuzzle.startNum + inPuzzle.size * inPuzzle.size 
- 2); i++)
   {
      flag = 0;
      for(row=0; row < inPuzzle.size; row++)
      {
         for(column=0; column < inPuzzle.size; column++)
         {
            if(inPuzzle.tiles[row][column] == i)
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

int IsSolved(flexiPuzzle inPuzzle)
{
   int row, column;
   if (inPuzzle.snake ==0)
   {
      for (row=0; row < inPuzzle.size; row++)
      {
         for(column=0; column < inPuzzle.size; column++)
         {
            
            if(row == inPuzzle.size-1 && column == inPuzzle.size -1 && inPuzzle.tiles[row][column] !=0)
            {
               return 0;
            }
            else if (inPuzzle.tiles[row][column] != inPuzzle.startNum++ && row != inPuzzle.size-1 && column != inPuzzle.size -1)
            {
              
 	       return 0;
            }
            
         }
      }
   }
    else
    {
      for (row=0; row < inPuzzle.size; row++)
      {
             if (row%2 ==0)
                 {
            for(column=0; column < inPuzzle.size; column++)
            {
                              if (row == inPuzzle.size -1 && column == inPuzzle.size -1 && inPuzzle.tiles[row][column] !=0)
                              {
                                 return 0;
                              }

                              else if (inPuzzle.tiles[row][column] != inPuzzle.startNum++ && row!= inPuzzle.size-1 && column != inPuzzle.size-1)
                  {
                     return 0;
                  }
            }
         }
                 else
                 {
                    for (column = inPuzzle.size-1; column >= 0; column--)
                        {
                              if (row == inPuzzle.size -1 && column == 0 && inPuzzle.tiles[row][column] !=0)
                              
                              {
                                 return 0;
                              }

                              else if (inPuzzle.tiles[row][column] != inPuzzle.startNum++ && row!=inPuzzle.size-1 && column !=0)
                  {
                     return 0;
                  }
             }

          }
      }
   }
      
   return 1;
}

double FindDistanceToSolution(flexiPuzzle inPuzzle)
{
	int row, column;
	double x =0;
	flexiPuzzle new;
	tilePosition tile1, tile2;
	new = SetPuzzle(inPuzzle.name, inPuzzle.size, inPuzzle.startNum, inPuzzle.snake);
	for(row=0; row < inPuzzle.size; row++)
	{
		for(column=0; column < inPuzzle.size; column++)
		{
			tile1 = GetPosition(new,new.tiles[row][column]);
			tile2 = GetPosition(inPuzzle,new.tiles[row][column]);
			x = x + ManhattanDistance(tile1, tile2);	
		}
	}
	
	return x / (inPuzzle.size*inPuzzle.size);
}

flexiPuzzle SetDistanceToSolution(flexiPuzzle inPuzzle, double distance)
{
	inPuzzle.distanceToSolution = distance;
	return inPuzzle;
}

int GetPlayerMove()
{
	int move;
	printf("Input your next move or -1 to exit ");
	scanf("%d", &move);
	return move;
}


int IsValidMove(flexiPuzzle inPuzzle, int tileNumber)
{
	int row, column;
	for (row=0; row <inPuzzle.size; row++)
	{
		for(column=0; column < inPuzzle.size; column++)
		{
			if(inPuzzle.tiles[row][column] == tileNumber)
			{
				/* TOP CORNERS */
				if (row ==0)
				{
					/*top left corner*/
					if (column ==0)
					{
						/*to the right*/
						if(inPuzzle.tiles[0][1] == 0)
						{
							return 1;
						}
						/*directly below*/
						else if (inPuzzle.tiles[1][0] == 0)
						{	
							return 1;
						}
					}
					/*top right corner*/
					else if (column == inPuzzle.size -1)
					{
						/*to the left*/
						if( inPuzzle.tiles[0][inPuzzle.size-2] == 0)
						{	
							return 1;
						}
						/*directly below*/
						else if(inPuzzle.tiles[1][inPuzzle.size -1] ==0)
						{	
							return 1;
						}
					}
					/*the rest of top row is edges*/
					else
					{
						/*to the right*/
						if (inPuzzle.tiles[0][column+1] == 0)
						{	
							return 1;
						}
						/*to the left*/
						else if (inPuzzle.tiles[0][column-1] == 0)
						{
							return 1;
						}
						/* below it*/
						else if (inPuzzle.tiles[1][column] == 0)
						{	
							return 1;
						}
					}
				}
					
					/*bottom corners*/
				else if( row == inPuzzle.size -1)
				{
					/*bottom left corner*/
					if (column == 0)
					{
						/* to the right*/
						if(inPuzzle.tiles[inPuzzle.size-1][1] == 0)
						{
							return 1;
						}
						/* above it*/
						else if (inPuzzle.tiles[inPuzzle.size-2][0] == 0)
						{
							return 1;
						}
					}
					/*bottom right corner*/
					else if (column == inPuzzle.size-1)
					{
						/*to the left*/
						if (inPuzzle.tiles[inPuzzle.size-1][inPuzzle.size-2] == 0)
						{	
							return 1;
						}
						/*above it*/
						else if (inPuzzle.tiles[inPuzzle.size-2][inPuzzle.size-1] ==0)
						{
							return 1;
						}
					}
					/*the rest of bottom row is edges*/
					else
					{
						/*to the right*/
						if (inPuzzle.tiles[inPuzzle.size-1][column+1] == 0)
						{
							return 1;
						}
						/*to the left*/
						else if (inPuzzle.tiles[inPuzzle.size-1][column-1] == 0)
						{
							return 1;
						}
						/* above it*/
						else if (inPuzzle.tiles[inPuzzle.size-2][column] == 0)
						{
							return 1;
						}
					}
				}
				/*checking the first and last column for edges*/
				else if (column ==0)
				{
					if (row !=0 && row!= inPuzzle.size-1)
					{
						/*right*/
						if(inPuzzle.tiles[row][1] == 0)
						{
							return 1;
						}
						/*above*/
						else if(inPuzzle.tiles[row-1][0] == 0)
						{
							return 1;
						}
						/*below*/
						else if (inPuzzle.tiles[row+1][0] ==0)
						{
							return 1;
						}
					}
				}
				else if (column == inPuzzle.size-1)
				{
					if( row!=0 && row != inPuzzle.size-1)
					{
						/*left*/
						if(inPuzzle.tiles[row][inPuzzle.size-2] ==0)
						{
							return 1;
						}
						/*above*/
						else if(inPuzzle.tiles[row-1][inPuzzle.size-1] == 0)
						{
							return 1;
						}
						/*below*/
						else if (inPuzzle.tiles[row+1][inPuzzle.size-1] ==0)
						{	
							return 1;
						}
					}
				}
				/*not corners or edres = neither!*/
				else
				{
					/*above*/
					if (inPuzzle.tiles[row-1][column] ==0)
					{	
						return 1;
					}
					/*below*/
					else if(inPuzzle.tiles[row+1][column] ==0)
					{	
						return 1;
					}
					/*left*/
					else if(inPuzzle.tiles[row][column-1] ==0)
					{	
						return 1;
					}
					/*right*/
					else if(inPuzzle.tiles[row][column+1] == 0)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

flexiPuzzle Move(flexiPuzzle inPuzzle, int tileNumber)
{
	int row, column, i;	

	if(IsValidMove(inPuzzle,tileNumber)==1)
	{
	for (row=0; row <inPuzzle.size; row++)
	{
		for(column=0; column < inPuzzle.size; column++)
		{
			if(inPuzzle.tiles[row][column] == tileNumber)
			{
				/* TOP CORNERS */
				if (row ==0)
				{
					/*top left corner*/
					if (column ==0)
					{
						/*to the right*/
						if(inPuzzle.tiles[0][1] == 0)
						{
							inPuzzle.tiles[0][1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
							for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*directly below*/
						else if (inPuzzle.tiles[1][0] == 0)
						{
							inPuzzle.tiles[1][0] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
					/*top right corner*/
					else if (column == inPuzzle.size -1)
					{
						/*to the left*/
						if( inPuzzle.tiles[0][inPuzzle.size-2] == 0)
						{
							inPuzzle.tiles[0][inPuzzle.size-2] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*directly below*/
						else if(inPuzzle.tiles[1][inPuzzle.size -1] ==0)
						{
							inPuzzle.tiles[1][inPuzzle.size-1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
					/*the rest of top row is edges*/
					else
					{
						/*to the right*/
						if (inPuzzle.tiles[0][column+1] == 0)
						{
							inPuzzle.tiles[0][column+1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*to the left*/
						else if (inPuzzle.tiles[0][column-1] == 0)
						{
							inPuzzle.tiles[0][column-1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/* below it*/
						else if (inPuzzle.tiles[1][column] == 0)
						{
							inPuzzle.tiles[1][column] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
				}
					
					/*bottom corners*/
				else if( row == inPuzzle.size -1)
				{
					/*bottom left corner*/
					if (column == 0)
					{
						/* to the right*/
						if(inPuzzle.tiles[inPuzzle.size-1][1] == 0)
						{
							inPuzzle.tiles[inPuzzle.size-1][1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/* above it*/
						else if (inPuzzle.tiles[inPuzzle.size-2][0] == 0)
						{
							inPuzzle.tiles[inPuzzle.size-2][0] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
					/*bottom right corner*/
					else if (column == inPuzzle.size-1)
					{
						/*to the left*/
						if (inPuzzle.tiles[inPuzzle.size-1][inPuzzle.size-2] == 0)
						{
							inPuzzle.tiles[inPuzzle.size-1][inPuzzle.size-2] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*above it*/
						else if (inPuzzle.tiles[inPuzzle.size-2][inPuzzle.size-1] ==0)
						{
							inPuzzle.tiles[inPuzzle.size-2][inPuzzle.size-1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
					/*the rest of bottom row is edges*/
					else
					{
						/*to the right*/
						if (inPuzzle.tiles[inPuzzle.size-1][column+1] == 0)
						{
							inPuzzle.tiles[inPuzzle.size-1][column+1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*to the left*/
						else if (inPuzzle.tiles[inPuzzle.size-1][column-1] == 0)
						{
							inPuzzle.tiles[inPuzzle.size-1][column-1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/* above it*/
						else if (inPuzzle.tiles[inPuzzle.size-2][column] == 0)
						{
							inPuzzle.tiles[inPuzzle.size-2][column] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
				}
				/*checking the first and last column for edges*/
				else if (column ==0)
				{
					if (row !=0 && row!= inPuzzle.size-1)
					{
						/*right*/
						if(inPuzzle.tiles[row][1] == 0)
						{
							inPuzzle.tiles[row][1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*above*/
						else if(inPuzzle.tiles[row-1][0] == 0)
						{
							inPuzzle.tiles[row-1][0] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*below*/
						else if (inPuzzle.tiles[row+1][0] ==0)
						{
							inPuzzle.tiles[row+1][0] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
				}
				else if (column == inPuzzle.size-1)
				{
					if( row!=0 && row != inPuzzle.size-1)
					{
						/*left*/
						if(inPuzzle.tiles[row][inPuzzle.size-2] ==0)
						{
							inPuzzle.tiles[row][inPuzzle.size-2] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*above*/
						else if(inPuzzle.tiles[row-1][inPuzzle.size-1] == 0)
						{
							inPuzzle.tiles[row-1][inPuzzle.size-1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
						/*below*/
						else if (inPuzzle.tiles[row+1][inPuzzle.size-1] ==0)
						{
							inPuzzle.tiles[row+1][inPuzzle.size-1] = tileNumber;
							inPuzzle.tiles[row][column] = 0;
								for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
							return inPuzzle;
						}
					}
				}
				/*not corners or edres = neither!*/
				else
				{
					/*above*/
					if (inPuzzle.tiles[row-1][column] ==0)
					{
						inPuzzle.tiles[row-1][column] = tileNumber;
						inPuzzle.tiles[row][column] = 0;
							for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
						return inPuzzle;
					}
					/*below*/
					else if(inPuzzle.tiles[row+1][column] ==0)
					{
						inPuzzle.tiles[row+1][column] = tileNumber;
						inPuzzle.tiles[row][column] = 0;
							for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
						return inPuzzle;
					}
					/*left*/
					else if(inPuzzle.tiles[row][column-1] ==0)
					{
						inPuzzle.tiles[row][column-1] = tileNumber;
						inPuzzle.tiles[row][column] = 0;
							for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
						return inPuzzle;
					}
					/*right*/
					else if(inPuzzle.tiles[row][column+1] == 0)
					{
						inPuzzle.tiles[row][column+1] = tileNumber;
						inPuzzle.tiles[row][column] = 0;
							for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							inPuzzle.moves[0] = tileNumber;
							if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
						return inPuzzle;
					}
				}
			}
		}
	}
	}
	else
	{
	    
			for(i=0; i < 50; i++)
							{
								if(inPuzzle.moves[i] == -2)
								{
									break;
								}
							}
							if(i==0)
							{
								inPuzzle.moves[i+1] = -2;
								inPuzzle.moves[0] = tileNumber;
							}
							for(; i>0; i--)
							{
								inPuzzle.moves[i+1] = inPuzzle.moves[i];
							}
							
		inPuzzle.moves[0] = -1;
	}
	if( !IsSolved(inPuzzle) && inPuzzle.moves[0] != -1)
	{
		inPuzzle.solved = 0;
	}
	return inPuzzle;
}

flexiPuzzle MoveSequence(flexiPuzzle inPuzzle, int movesArray[],int numberOfMoves)
{
	flexiPuzzle copy;
	int i;
	copy = SetPuzzleTo(inPuzzle);
	
	for (i=0; i<numberOfMoves; i++)
	{
		copy = Move(copy, movesArray[i]);
		if (copy.moves[i]==-1)
		{
			return copy;
		}
	}
	return copy;
}

flexiPuzzle RandomMove(flexiPuzzle inPuzzle)
{
	int moves,row,column,i, counter, savetile; 	
	
	for (row=0; row<inPuzzle.size; row++)
	{
		for(column=0; column < inPuzzle.size; column ++)
		{
		   
			if (inPuzzle.tiles[row][column] == 0)
			{
			/*ALL CORNERS*/
				if ((row ==0 || row == inPuzzle.size-1) && (column ==0 || column == inPuzzle.size-1))
				{
					moves = 2;
               
               					
				}
				/*EDGES ON TOP AND BOTTOM ROW*/
				else if ((row ==0 || row == inPuzzle.size-1) && (column !=0 || column != inPuzzle.size-1))
				{
					moves = 3;
					
				}
				else if ((row!=0 || row != inPuzzle.size-1) && (column ==0 || column == inPuzzle.size-1))
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

	for (row=0; row<inPuzzle.size; row++)
	{
		for(column=0; column < inPuzzle.size; column ++)
		{ 
		    
		
			if(IsValidMove(inPuzzle,inPuzzle.tiles[row][column]) == 1)
			{
				if (counter >0)
				{
					counter --;
				}
				else if (counter ==0)
				{
				inPuzzle = Move(inPuzzle,inPuzzle.tiles[row][column]);
					return inPuzzle;
				}
			}
		}
	}

	return inPuzzle;
}

flexiPuzzle Shuffle(flexiPuzzle inPuzzle, int numberOfMoves)
{
	int i;
	for (i=0; i<numberOfMoves; i++)
	{
		inPuzzle= RandomMove(inPuzzle);
		if(inPuzzle.moves[0] == -1)
		{
			
			return inPuzzle;
		}
		
	}
	return inPuzzle;
}