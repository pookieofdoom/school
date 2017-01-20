#ifndef PROBLEM2_H
#define PROBLEM2_H

/* Description:
 *   Changes the bit-value at the specfied location in the specfied value to
 *   the specified bit-value.
 *
 *   NOTE: There is no "complexity" requirement for this problem.
 *
 * Parameters:
 *      value: The value who's bit is to be set.
 *         at: The bit to modify. An "at" of 0 would indicate the right-most
 *             (least significant) bit and a value of 31 would indicate the
 *             left-most (most-significant) bit.
 *   bitValue: The bit value (0 or 1) to set at the specfied location in value.
 *
 * Return:
 *    void
 *
 * Restrictions:
 *   1) You may NOT use any loops in your soluiton.
 *
 * Assumptions:
 *   1) You may assume "at" is between 0 and 31 inclusive - no error checking
 *      required.
 *   2) You may assume "bitValue" is 0 or 1 - no error checking required.
 */
void setBit(unsigned int *value, int at, int bitValue);

#endif
