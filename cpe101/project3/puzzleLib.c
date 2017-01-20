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


