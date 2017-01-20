#ifndef PROBLEM1_H
#define PROBLEM1_H 

/* Creates and returns a new string allocated on the heap (malloc/calloc)
 * comprised of the prefix string followed by the str string. For example,
 * if str was "XYZ" and prefix was "ABC" the function would return "ABCXYZ".
 * Handles any and all valid C strings including empty strings.
 *
 * NOTES:
 *   1) Except for malloc/calloc, you MAY NOT use any Standard Library
 *      functions or your code is likely to FAIL BENDER.
 *   2) You MAY NOT use array syntax in your solution or your code is likely
 *      to FAIL BENDER.
 *   3) You may, but are not required, write any additional helper functions
 *      and use them in your solution if you wish. They must be in the same
 *      source file as your implementation of this function.
 */
char* prepend(const char* str, const char* prefix);

#endif
