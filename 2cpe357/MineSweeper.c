#include <stdio.h>
#include <stdlib.h>
#define MAX_ROW 20
#define MAX_COL 20
#define HIDDEN_BIT 7
#define HIDDEN_MASK (1 << HIDDEN_BIT)
#define HIDDEN(x) ( (x) & HIDDEN_MASK)
#define MAKE_VISIBLE(x) ( (x) ^ HIDDEN_MASK)
#define VISIBLE_ZERO 0x30
#define HIDDEN_ZERO 0xB0
#define VISIBLE_MINE 0x58
#define HIDDEN_MINE 0xD8

//use the first bit to determine if the tile is hidden or not


//function prototypes
int initMines(int mineArray[MAX_ROW][MAX_COL]);
void printBoard(int mineArray[MAX_ROW][MAX_COL], int choiceRow, int choiceCol);
void initBoard(int mineArray[MAX_ROW][MAX_COL]);
void floodfill(int mineArray[MAX_ROW][MAX_COL], int row, int col);
void revealAll(int mineArray[MAX_ROW][MAX_COL]);

int main() {
   int mineArray[MAX_ROW][MAX_COL];
   int mineCount;
   int minePlacement = 0;
   int row, col;
   int loseFlag = 0; //if 1 you lose
   int roundCount = 0;
   
   //initialize all spaces to hidden 0
   for(row = 0; row < MAX_ROW; row++) {
      for(col = 0; col < MAX_COL; col++) {
         mineArray[row][col] = HIDDEN_ZERO;
      }
   }
   
   //place all the mines and keep track of how many are there
   mineCount = initMines(mineArray);
   
   //starting board with everything hidden and calculates spacing of each tile
   initBoard(mineArray);

   //loop until lose or win
   //probably should move win condition into printboard so it doesnt check that twice
   while (loseFlag != 1) {
      //check if win condition is met
      if(numberOfHidden(mineArray) == mineCount) {
         printf("You Win!!!!\n");
         revealAll(mineArray);
         printBoard(mineArray, row, col);
         return 0;
      }
      
      //take in input from user
      if(scanf("%d %d", &row, &col) != EOF) {
         if(row < 0 || row > (MAX_ROW-1) || col < 0 || col > (MAX_COL-1)) {
            printf("(%d, %d) is not a valid position.\n", row, col);
         }
         if(HIDDEN(mineArray[row][col]) == 0 && !(row < 0 || row > (MAX_ROW -1) || col < 0 || col > (MAX_COL - 																																			1))) {
            printf("Spot already revealed, pick another spot\n");
         }
         

            
            if(mineArray[row][col] == HIDDEN_MINE) {
               loseFlag = 1; 
            }
               printf("Round: %d\n", roundCount);
               roundCount++;

            printBoard(mineArray, row, col);

         }
         
      else {
         printf("No more input. Game Over.\n");
         revealAll(mineArray);
         printBoard(mineArray, row, col);
         return 0;
      }

   }
	printf("You Lose...\n");
   revealAll(mineArray);
   printBoard(mineArray, row, col);
   return 0;
}


int initMines(int mineArray[MAX_ROW][MAX_COL]) {
   int mineCount;
   int minePlacement = 0;
   int row, col;
   scanf("%d", &mineCount);
   if(mineCount < 0) {
      printf("Number of mines cannot be negative.\n");
      exit(0);
   }
   while(minePlacement != mineCount) {
      //remember to check if user accidentlys puts same mine location ... 
      if (scanf("%d %d", &row, &col) != EOF) { 
         while((row < 0 || row >(MAX_ROW-1) || col < 0 || col > (MAX_COL-1)) || mineArray[row][col] == 																															     HIDDEN_MINE) {
            printf("(%d, %d) is not a valid position for a mine.\n", row, col);
            scanf("%d %d", &row, &col);
         }
            //set mines to hidden X which is 0xD8
            mineArray[row][col] = HIDDEN_MINE;
            minePlacement++;
         
      }
      else {
         printf("Not enough mines placed on the board.\n");
         exit(0);
      }
   }
   return mineCount;

}

void printBoard(int mineArray[MAX_ROW][MAX_COL], int choiceRow, int choiceCol) {
   int row, col;
   if(!(choiceRow < 0 || choiceRow > (MAX_ROW -1) || choiceCol < 0 || choiceCol > (MAX_COL-1))) {
      floodfill(mineArray, choiceRow, choiceCol);   
   }
   for(row = 0; row < MAX_ROW; row++) {
      for(col = 0; col < MAX_COL; col++) {
         if(HIDDEN(mineArray[row][col])) {
            printf("* ");
         }
         else {
            printf("%c ", mineArray[row][col]);
         }
      }
      printf("\n");
   }

}

void initBoard(int mineArray[MAX_ROW][MAX_COL]) {
   int row, col;
   printf("Initial Board: \n");

   for(row = 0; row < MAX_ROW; row++) {
      for(col = 0; col <MAX_COL; col++) {
         if(HIDDEN(mineArray[row][col])) {
            printf("* ");
         }
         //setup the board so that it shows how many spaces the tile is from the mine
         if(mineArray[row][col] == HIDDEN_MINE) {
            //top left of mine
            if(row != 0 && col != 0 && mineArray[row-1][col-1] != HIDDEN_MINE) {
               mineArray[row-1][col-1]++;
            }
            //top of mine
            if(row != 0 && mineArray[row-1][col] != HIDDEN_MINE) {
               mineArray[row-1][col]++;
            }
            //top right of mine
            if(row != 0 && col != (MAX_COL-1) && mineArray[row-1][col+1] != HIDDEN_MINE) {
               mineArray[row-1][col+1]++;
            }
            //left of mine
            if(col != 0 && mineArray[row][col-1] != HIDDEN_MINE) {
               mineArray[row][col-1]++;
            }
            //right of mine
            if(col != (MAX_COL-1) && mineArray[row][col+1] != HIDDEN_MINE) {
               mineArray[row][col+1]++;
            }
            //bottom left of mine
            if(row != (MAX_ROW-1) && col != 0 && mineArray[row+1][col-1] != HIDDEN_MINE) {
               mineArray[row+1][col-1]++;
            }
            //bottom of mine
            if(row != (MAX_ROW-1) && mineArray[row+1][col] != HIDDEN_MINE) {
               mineArray[row+1][col]++;
            }
            //bottom right of mine
            if(row != (MAX_ROW-1) && col != (MAX_COL-1) && mineArray[row+1][col+1] != HIDDEN_MINE) {
               mineArray[row+1][col+1]++;
            }
         }
         
      }
      printf("\n");
   } 
   
}

void floodfill(int mineArray[MAX_ROW][MAX_COL], int row, int col) {
   //not hidden or not 0
   if(HIDDEN(mineArray[row][col]) == 0) {
      return ;
   }
   mineArray[row][col] = MAKE_VISIBLE(mineArray[row][col]);
   
   if(mineArray[row][col] != VISIBLE_ZERO) {
      return ;
   }

   //top left
   if(row !=0 && col != 0) {
      floodfill(mineArray, row-1, col-1);
   }
   //top
   if(row !=0) {
      floodfill(mineArray, row-1, col);
   }
   //top right
   if(row != 0 && col != (MAX_COL-1)) {
      floodfill(mineArray,row-1, col+1);
   }
   //left
   if(col != 0) {
      floodfill(mineArray, row, col-1);
   }
   //right
   if(col != (MAX_COL-1)) {
      floodfill(mineArray, row, col+1);
   }
   //bottom left
   if(row != (MAX_ROW-1) && col != 0) {
      floodfill(mineArray, row+1,col-1);
   }
   //bottom
   if(row != (MAX_ROW-1)) {
      floodfill(mineArray, row+1, col);
   }
   //bottom right
   if(row !=(MAX_ROW-1) && col != (MAX_COL-1)) {
      floodfill(mineArray, row+1, col+1);
   }
   
}

void revealAllMines(int mineArray[MAX_ROW][MAX_COL]) {
   int row, col;
   for(row =0; row < MAX_ROW; row++) {
      for(col =0; col < MAX_COL; col++) {
         if(HIDDEN(mineArray[row][col]) && mineArray[row][col] == HIDDEN_MINE) {
            mineArray[row][col] = MAKE_VISIBLE(mineArray[row][col]);
         }
      }
   }
}

int numberOfHidden(int mineArray[MAX_ROW][MAX_COL]) {
   int row, col;
   int count = 0;
   for(row =0; row <MAX_ROW; row++) {
      for(col=0; col < MAX_COL; col++) {
         if(HIDDEN(mineArray[row][col])) {
            count++;
         }
      }
   }
   return count;
}

void revealAll(int mineArray[MAX_ROW][MAX_COL]) {
   int row, col;
   for(row =0; row < MAX_ROW; row++) {
      for(col = 0; col < MAX_COL; col ++) {
         if(HIDDEN(mineArray[row][col])) {
            mineArray[row][col] = MAKE_VISIBLE(mineArray[row][col]);
         }
      }
   }
                               
   
}
                                      
                                      




