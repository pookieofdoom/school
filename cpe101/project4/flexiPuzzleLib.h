/* flexiPuzzle library header file 
 * the struct version
 * Foaad Khosmood / Spring 2013 */

#define MAX_PUZZLE_SIZE 10
#define MAX_NAME_LENGTH 20
#define MOVE_HISTORY_SIZE 50

/* this is the default number of shuffle moves, a multiple of size */
#define DEFAULT_SHUFFLE_MOVES MAX_PUZZLE_SIZE * 25

/* this is used to specify number of moves for bulk move operations */
#define DEFAULT_N_MOVES 20

/* main puzzle data type */
typedef struct {
   char name[MAX_NAME_LENGTH]; /* a name for the puzzle */
   int tiles[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE]; /* tile content */
   int size;                   /* true size <= MAX_PUZZLE_SIZE */
   int startNum;               /* starting tile number */
   int snake;                  /* is the puzzle snake?(1) or not (0) */
   int moves[MOVE_HISTORY_SIZE + 1]; /* a history of moves, moves[0] 
				  * is the latest move. A -2 indicates
				  * a termination token if < 50 */
   int solved;                 /* boolean: is puzzle solved? */
   double distanceToSolution;  /* a heuristic =  how far the puzzle is
			        * from being solved. A solved puzzle has
			        * distanceToSolution = 0.0 */
} flexiPuzzle;

/* another useful data type */
typedef struct {
   int row;
   int column;
} tilePosition;


/* flexiPuzzleLib functions. Do not modify */
void PrintPuzzle(flexiPuzzle inPuzzle); /* print a given puzzle */

/* sets the name of the puzzle to name, overwrites anything that may have been there before 
 * if the length of name[] is greater than MAX_NAME_LENGTH than only the first MAX_NAME_LENGTH 
 * of the name[] are copied into the inPuzzle.name */ 
flexiPuzzle SetPuzzleName(flexiPuzzle inPuzzle,char name[]);

/* create a new puzzle and return it. Use name, size, startNum and snake from arguments 
 * to set the tiles[][], solved and distanceToSolution (should be 0.0) 
 * the moves[] array's first element should be set to -2 to denote a history of size 0 */
flexiPuzzle SetPuzzle(char name[], int size, int startNum, int snake); /* [snake] is either 0 or 1. */

/* return inPuzzle's true size by reading it from the structure */
int GetSize(flexiPuzzle inPuzzle);

/* printf() this puzzle's name. No other info, space or punctuation. Just the name */
void PrintName(flexiPuzzle inPuzzle);

/* return inPuzzle's start number by reading it from the structure */
int GetStartNum(flexiPuzzle inPuzzle);

/* return inPuzzle's snake attribute (0 for regular, 1 for snake configuration) */
int GetSnakeStatus(flexiPuzzle inPuzzle);

/* sets all the values of a new puzzle to inPuzzle, then return it */
flexiPuzzle SetPuzzleTo(flexiPuzzle inPuzzle);

/* returns true if *all* components of puzzle1 are same as puzzle2 */
int IsIdentical(flexiPuzzle puzzle1, flexiPuzzle puzzle2);

/* returns true only if tiles, size, startNum and snake are identical.
 * If any of those are not the same, then return 0.
 * Ignore other values such as name, moves[] distanceToSolution, etc.  */
int IsSameState(flexiPuzzle puzzle1, flexiPuzzle puzzle2);

/* similar to previous project, return 0 if puzzle is not valid.
 * return 1 after you make sure that only one of each correct tile number is
 * represented */
int IsValidPuzzle(flexiPuzzle inPuzzle);

/* sets the "solved" component to the one passed in, returns whole puzzle */
flexiPuzzle SetSolvedState(flexiPuzzle inPuzzle, int solved);

/* sets the "distanceToSolution" compoment to the one passed in, returns whole puzzle */
flexiPuzzle SetDistanceToSolution(flexiPuzzle inPuzzle, double distance);

/* returns 1 if puzzle is solved, 0 otherwise */
int IsSolved(flexiPuzzle inPuzzle);

/* obtain a valid player move, or special flag (-1 for exit) and
 *    return it */
int GetPlayerMove();

/* this function returns the position of the [tileNum] tile */
tilePosition GetPosition(flexiPuzzle inPuzzle, int tileNumber);

/* returns 1 if the two positions are the same, 0 otherwise */
int IsSamePosition(tilePosition position1, tilePosition position2);

/* calculates the Manhattan Distance (MD) between the two postions
 * MD is just the difference between rows + difference between columns */
int ManhattanDistance(tilePosition position1, tilePosition position2);

/* calculates a distance to solution based on the average (per tile) 
 * Manhattan distance of every tile's current position with it's solved-state position */
double FindDistanceToSolution(flexiPuzzle inPuzzle);

/* reads the value of DistanceToSolution from inPuzzle and returns it */
double GetDistanceToSolution(flexiPuzzle inPuzzle);

/* return 1 if the move is valid, 0 otherwise */
int IsValidMove(flexiPuzzle inPuzzle, int tileNumber);

/* make one move: switch the empty tile with the one passed in.
 *    returns post-move state if success, or same puzzle state if move is not possible 
 *    A successful move is recorded in the moves[] array. 
 *    An invalid move is also recorded as a "-1" in the moves[] array 
 *    If a Move is successfully made on a puzzle that was solved, the solved component should 
 *    change to 0. This function should not set solved to 1, however. */
flexiPuzzle Move(flexiPuzzle inPuzzle, int tileNumber);

/* this function makes [numberOfMoves]  moves in a row, the moves 
 * themselves are given  in the first array argument [movesArray]. 
 * returns the whole puzzle in post-move state if successfull, pre-move state
 * if not successfull. All moves have to work for it to be a success. History
 * is updated just like Move().  */
flexiPuzzle MoveSequence(flexiPuzzle inPuzzle, int movesArray[],int numberOfMoves);

/* makes a random valid move, returns new post-move puzzle. Updates history. */    
flexiPuzzle RandomMove(flexiPuzzle inPuzzle);

/* make [numberOfMoves] random moves in a row, returns the post-move puzzle 
 * if all succeed. Otherwise, the same inPuzzle */
flexiPuzzle Shuffle(flexiPuzzle inPuzzle, int numberOfMoves); 
