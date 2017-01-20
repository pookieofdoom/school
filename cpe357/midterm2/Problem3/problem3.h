#ifndef PROBLEM3_H
#define PROBLEM3_H

/* Technically this #include is not needed but it is included to help
 * remind students that they must be using SmartAlloc in their solution.
 */
#include "SmartAlloc.h" 

/* Returns the new array that results from combining the "from" and "to"
 * arrays. The values in the "from" array are insert into the "to" array
 * beginning at the specified index, "at". For example, if the "to" array
 * contained {9, 3, 8}, the "from" array contained {-7, 5}, and "at" index
 * was 2 then the resulting array would be {9, 3, -7, 5, 8}.
 *
 * NOTE:
 * 
 *   1) The "to" array is assumed to have been allocated from the heap and
 *      must be freed by this function.
 *   2) The resulting array MUST be exactly the size necessary to hold to
 *      combined values of "from" and "to" no more, no less.
 *   3) Your solution must work on both a 32-bit and a 64-bit computer. You
 *      should try it on both if you have time (vogon, unix1, unix2, unix3,
 *      and unix4 are 32-bit machines, unix11, unix12, unix13, unix14 and
 *      most CSL workstations are 64-bit machines).
 *
 * IMPORTANT ASSUMPTIONS YOU MAY MAKE FOR THIS FUNCTION:
 *
 *   1) All parameters are reasonable and valid. Specifically,
 *      a) The array pointers will not be NULL.
 *      b) The sizes will be correct.
 *      c) The "at" index will not be negative or greater than the size of
 *         the "from" array.
 *
 * IMPORTANT REQUIREMENTS YOU MUST MEET FOR THIS FUNCTION:
 *
 *   1) You MUST USE SmartAlloc in your solution. Both SmartAlloc.c and
 *      SmartAlloc.h are provided.
 *   2) You MAY NOT USE array syntax in your solution.
 *   3) You MAY NOT USE any loops or recurison in your soluiton. You are
 *      exected to use the appropriate memory functions from the C Std. Lib. -
 *      some documentation may be provide during the exam and you MAY USE the
 *      man pages.
 */
int* insertArray(const int *to,     /* Pointer to array to insert into */
                 int toSize,        /* Size of the "to" array */
                 int at,            /* The index to begin insertion in "to" */
                 const int *from,   /* Pointer to array to insert */
                 int fromSize);     /* Size of the "from" array */

#endif
