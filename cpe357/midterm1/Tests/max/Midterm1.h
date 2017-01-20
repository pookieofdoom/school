#ifndef MIDTERM1_H
#define MIDTERM1_H
/*
 * CSC 357 W15 Midterm 1 Header file
 *
 * -- DO NOT MODIFY --
 *
 * IMPORTANT NOTES:
 *
 *    1) Make sure your funcitons in Midterm1.c match or your submission
 *       may NOT compile or may not work as expected and required.
 *
 *    2) This midterm is primarily testing your skills with pointers. Therefore
 *       you MAY NOT USE ARRAY SYNTAX ANYWHERE IN YOUR SOURCE. Specifically,
 *       you MAY NOT USE the [ ] operator to index into an array OR YOUR CODE
 *       WILL NOT BE EVALUATED BY BENDER AND YOU WILL RECEIVE A ZERO FOR THE
 *       ENTIRE MIDTERM.
 */

typedef struct {
   int from;
   int length;
} LASResult;

/* Determines the maximum of two values pass in by address and returns it 
 * as a value. 
 *
 * Parameters:
 *    a: A pointer to an integer value.
 *    b: A pointer to an integer value.
 *
 * Return:
 *    Returns the maximum value.
 */
int max(int *a, int *b);

/* Swaps two double's values for the caller.
 *
 * Parameters:
 *    a: A pointer to a double value.
 *    b: A pointer to a double value.
 *
 * Return:
 *    The parameter a's value will be what b's was and the parameber b' value
 *    will be what a's was when the function was called.
 */
void swap(double *a, double *b);

/* Return the sum of of all elements in an array WITHOUT USING array syntax.
 * This means you MAY NOT USE the [ ] operator to index into the array and
 * MUST INSTEAD use pointer syntax and pointer arithmetic.
 *
 * IF YOUR SOLUTION USES [ ] ANYWHERE IT WILL NOT COMPILE AND RECEIVE A ZERO!
 *
 * Parameters:
 *    array: The array of double values to sum.
 *    size: The number of elements in the array.
 *
 * Return:
 *    The sum of the values in the array or zero if the array is empty.
 */
double sum(double *array, int size);

/* Finds the Longest Ascending Sequence (LAS) of values found in the array 
 * WITHOUT USING array syntax and returns it's starting index and length in
 * the provided struture. You MAY NOT USE the [ ] operator to index into the
 * array and MUST INSTEAD use pointer syntax and pointer arithmetic.
 *
 * IF YOUR SOLUTION USES [ ] ANYWHERE IT WILL NOT COMPILE AND RECEIVE A ZERO!
 *
 * To be considered an ascending sequence all values in the sequence must be 
 * greater than the immediately preceding value, if any AND the length of the
 * sequence must be at least 2.
 *
 * Parameters:
 *    array: The array to search for ascending sequences.
 *    size: The size of the array.
 *    result: A pointer to the struct to return information in.
 *
 * Return:
 *    The LASResult struct's from-value will be the index of the first value in
 *    the first longest ascending sequence and the LASResult struct's
 *    length-value will be the number of values in the sequence. If there is
 *    no ascending sequence the LASResult struct's from will be set to -1 and
 *    the LASResult struct's length will be set to zero by this function.
 */
void las(int *array, int size, LASResult *result);

#endif
