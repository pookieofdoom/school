	/* 
 * types.c
 * <Edit this! Your Name Here>
 * Output a message given a set of data.
 * Rules:
 *  - You may not create any additional variables.
 *  - You may not edit any of the code that was given to you, 
 *     unless otherwise stated in the comments.
 *  - You may only add printf statements to the code.
 *  - You must use every variable, and they may not be used 
 *     more than once (you have all the data you need).
 *  - Your output should match this exactly:
      Why do programmers mix up Christmas and Halloween?      Because DEC 25 = OCT 31 *
 */

#include <stdio.h>

int main(void) {
	char x1 = 'D', x2 = 'T', x3 = ' ', x4 = 'C', x5 = ' ', x6 = '5', x7 = 'O';
	int y1 = 2, y2 = 51, y3 = 32, y4 = 67, y5 = 1, y6 = 69, y7 = 32, y8 = 61;
	
	printf("Why do programmers mix up Christmas and Halloween?\n");
	printf("Because ");
	
	/* Edit below this comment only */
        printf("%c%c%c%c%d%c%c%c%c%c%c%c%c%c%d", x1, y6, x4, x3, y1, x6, x5, y8, y3, x7, y4, x2, y7, 		y2,y5);           
	
	/* Edit above this comment only */
	
	printf("\n");
	return 0;
}
