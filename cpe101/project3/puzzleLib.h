/* puzzle library header file 
 * Foaad Khosmood / Spring 2013 */
 

/* size of the puzzle, 3 means 8-puzzle, 4 means 15-puzzle, etc. */
#define PUZZLE_SIZE 4

/* this is the default number of shuffle moves, a multiple of size */
#define DEFAULT_SHUFFLE_MOVES PUZZLE_SIZE * 25

/* this is used to specify number of moves for bulk move operations */
#define DEFAULT_N_MOVES 20

/* library functions. Do not modify these function prototypes */

void PrintPuzzle(int inPuzzle[PUZZLE_SIZE][PUZZLE_SIZE]); /* print a given puzzle */
void SetPuzzle(int inPuzzle[PUZZLE_SIZE][PUZZLE_SIZE], int startNum, int snake); /* [snake] is either 0 or 1. */
void SetPuzzleTo(int inPuzzle[][PUZZLE_SIZE], int outPuzzle[][PUZZLE_SIZE]);
int IsEqual(int puzzle1[][PUZZLE_SIZE], int puzzle2[][PUZZLE_SIZE]);
int IsValidPuzzle(int inPuzzle[][PUZZLE_SIZE],int startNum);
int IsSolved(int inPuzzle[][PUZZLE_SIZE], int startNum, int snake);
