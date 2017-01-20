#include "problem3.h"

/* Description:
 *   Determines if a Stack is empty or not.
 *
 * Parameters:
 *   top - A pointer to the top of a stack, NULL means it's empty.
 *
 * Return:
 *   True if the stack is empty, otherwise false.
 */
int isEmpty(const Stack *top) {
   if(top)
      return 0;
   return 1;
   
}

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
void push(Stack **top, double value) {
   Stack *temp = malloc(sizeof(Stack));
   temp->value = value;
   temp->next = *top;
   *top = temp;
      
}

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
double pop(Stack **top) {
   Stack *temp = *top;
   double value = temp->value;
   *top = (*top)->next;
   free(temp);
   return value;
}