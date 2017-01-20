#ifndef PROBLEM3_H
#define PROBLEM3_H

#include <stdlib.h>
#include "SmartAlloc.h"

/* The structure that MUST be used to represent an element in a Stack */
typedef struct Stack {
   double value;
   struct Stack *next;
} Stack;

/* GENERAL NOTES
 * 
 *   1) A stack is a First-In-Last-Out data structure. The classic operations
 *      on a stack are "push" to add values and "pop" to remove values. For
 *      example, if you called push(1), push(2), and push(3) and the pop()
 *      three times the first pop() would return 3, the second pop() would
 *      return 2, and the third pop() would return 1.
 *   2) For this problem you must implement a stack using a linked list of
 *      Stack structures (defined above). 
 *   3) You MUST allocate all Stack structs on the heap using SmartAlloc and
 *      must free all memory no longer is use.
 *   4) There are NO RESTRICTIONS on C language features or C Standard Library
 *      functions you may use in your solution.
 *   5) You MAY ASSUME:
 *      a) A NULL stack pointer represents an empty stack - this must be the
 *         case after popping the last element on a stack too.
 *      b) The pop function will NOT BE CALLED on an empty stack
 */

/* Description:
 *   Determines if a Stack is empty or not.
 *
 * Parameters:
 *   top - A pointer to the top of a stack, NULL means it's empty.
 *
 * Return:
 *   True if the stack is empty, otherwise false.
 */
int isEmpty(const Stack *top);

/* Description:
 *   Adds the specfied value to the "top" of the specified stack. 
 *   The memory for each Stack struct must be allocated from the
 *   heap using SmartAlloc.
 *
 * Parameters:
 *   top - A pointer-to-a-pointer to the top of a Stack. This parameter acts
 *         as an output parameter, i.e., this function must update top for
 *         the caller. Note that top may point to a NULL pointer, this
 *         indicates you are pushing onto an empty stack.
 *   value - The value to add to the "top" of the stack.
 *
 * Return:
 *   void 
 */
void push(Stack **top, double value);

/* Description:
 *   Removes and returns the value at the "top" of the specified stack. The
 *   memory associated with the popped Stack struct is freed.
 *
 * Parameters:
 *   top - A pointer-to-a-pointer to the top of a Stack. This parameter acts
 *         as an output parameter, i.e., this function must update top for
 *         the caller. This function will set pointer that top points TO to
 *         NULL when poping the last element in the stack.
 *
 * Return:
 *   The value that was removed from the top of the stack. 
 */
double pop(Stack **top);

#endif
