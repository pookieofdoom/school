#ifndef PROBLEM1_H
#define PROBLEM1_H

/* Description:
 *   Returns the bit-value at the specified location in the specified value.
 *
 *   NOTE: There is no "complexity" requirement for this problem.
 *
 * Parameters:
 *   from: The value containing the bit we are interested in getting.
 *     at: Which bit to return. An "at" of 0 would indicate the right-most
 *         (least significant) bit and a value of 31 would indicate the
 *         left-most (most-significant) bit.
 *
 * Return:
 *   The value of the bit at the specfied location, i.e., 0 or 1.
 *
 * Restrictions:
 *   1) You may NOT use any loops in your soluiton.
 *
 * Assumptions:
 *   1) You may assume "at" will be between 0 and 31, inclusive - no error
 *      checking required.
 */
int getBit(unsigned int from, int at);

#endif
