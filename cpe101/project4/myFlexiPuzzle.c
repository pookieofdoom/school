#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flexiPuzzleLib.h"

#define BOUND 99
#define DEFAULT_NAME "Anthony Puzzle"

int main()
{
	char answer;
	flexiPuzzle myPuzzle;
	int var,count=0, m;
	srandom(time(NULL));
	system("clear");
	printf("Welcome to the Flexi Puzzle Program!\n");
	printf("\nWhat size puzzle would you like? ");
	scanf("%d", &myPuzzle.size);
	while(myPuzzle.size <3 || myPuzzle.size >10)
	{
		printf("Invalid entry. It should be between 3 and 10 inclusive. Please try again. ");
		scanf("%d", &myPuzzle.size);
	}

	printf("What configuration (r)egular or (s)nake? ");
	scanf(" %c", &answer);
	while (answer != 'r' && answer!= 's')
	{
		printf("Invalid entry. It should be either 'r' or 's'. Please try again. ");
		scanf(" %c", &answer);
	}
	
	printf("What starting number? ");
	scanf("%d", &myPuzzle.startNum);
	while (myPuzzle.startNum <=0 || myPuzzle.startNum > BOUND - myPuzzle.size*myPuzzle.size + 2)
	{
		printf("Invalid entry. It should be between 1 and %d inclusive. Please try again ", BOUND - myPuzzle.size*myPuzzle.size + 2);
		scanf("%d", &myPuzzle.startNum);
	}
	
	if(answer == 'r')
	{
		var = 0;
		myPuzzle = SetPuzzle(DEFAULT_NAME, myPuzzle.size, myPuzzle.startNum, var);
		
		
	}
	else if (answer == 's')
	{
		var = 1;
		myPuzzle = SetPuzzle(DEFAULT_NAME, myPuzzle.size, myPuzzle.startNum, var);
		
		
	}
	
	myPuzzle = Shuffle(myPuzzle, DEFAULT_SHUFFLE_MOVES);
	myPuzzle = SetDistanceToSolution(myPuzzle,FindDistanceToSolution(myPuzzle));
	if(IsSolved(myPuzzle))
				{
					myPuzzle = SetSolvedState(myPuzzle,1);
				}
	system("clear");
	PrintPuzzle(myPuzzle);
	printf("[%d] ", count);
	m = GetPlayerMove();
	
	while(m != -1)
	{
	
		if (m == -1)
		{
			
			break;
		}
		else if (m <=0 || m >= myPuzzle.size*myPuzzle.size)
		{
			printf("Invalid move!\n");
		}
		else
		{
			if(IsValidMove(myPuzzle,m))
			{
				myPuzzle = Move(myPuzzle,m);
				myPuzzle = SetDistanceToSolution(myPuzzle,FindDistanceToSolution(myPuzzle));
				if(IsSolved(myPuzzle))
				{
					myPuzzle = SetSolvedState(myPuzzle,1);
				}
				system("clear");
				count ++;
				PrintPuzzle(myPuzzle);
				printf("[%d] ", count);
			}
			else
			{
				printf("Invalid Move!\n ");
				PrintPuzzle(myPuzzle);
				printf("[%d] ", count);
			}
			
		}
		m = GetPlayerMove();
		
	}
	if (IsSolved(myPuzzle))
	{
		printf("\nCongratulations! You solved the puzzle in %d moves. Thanks for playing!\n", count);
	}
	else
	{
		printf("\nThanks for playing!\n\n");
	}

   return 0;
}
   
