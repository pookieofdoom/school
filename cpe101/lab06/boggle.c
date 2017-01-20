#include <stdio.h>
#include <stdlib.h>
#define DIM 4
#define VOWEL 6

void makeBoard(char board[][DIM]);
void printBoard(char board[][DIM]);
int isValid(char board[][DIM]);

int main()
{
   int seed;
   char answer;
   char board[DIM][DIM];
   printf("Enter seed: ");
   scanf("%d", &seed);
   srand(seed);
   
   do
   {
      makeBoard(board);
      while (!isValid(board))
      {
         makeBoard(board);
      }
      printBoard(board);
      
      printf("Again (y/n)? ");
      scanf(" %c", &answer);    
   } 
   while (answer == 'y');

      return 0;
   
}

void makeBoard(char board[][DIM])
{
   int row,col;
   int x;
   
   for (row=0; row<DIM; row++)
   {
      for (col=0; col<DIM; col++)
	  {	     
	     x = rand()%26 + 65;
		 board[row][col] = x;
      }
   }
}

void printBoard(char board[][DIM])
{
   int column,row;
   for (row=0;row < DIM;row++)
   {
      for(column=0;column < DIM;column++)
      {
      
         printf("%c", board[row][column]);
         
        
     }   
   printf("\n");	 
   }
}

int isValid(char board[][DIM])
{
   int row, column, count=0;
   for (row=0; row<DIM; row++)
   {
      for(column=0; column< DIM; column++)
      {
         if (board[row][column] == 'A')
		 {
		    count++;
	     }
		 else if(board[row][column] == 'E')
		 {
		    count++;
		 }
		 else if(board[row][column] == 'I')
		 {
		    count++;
	     }
		 else if(board[row][column] == 'O')
		 {
		    count++;
		 }
		 else if(board[row][column] == 'U')
		 {
		    count++;
	     }
      }
   }
   if (count <VOWEL)
   {
      return 0;
   }
   else
   {
      return 1;
   }
}  