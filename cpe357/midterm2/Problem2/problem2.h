#ifndef PROBLEM2_H
#define PROBLEM2_H

#include <stdlib.h>      // Needed for #define of NULL
#include "SmartAlloc.h"  // MUST be included after stdlib.h

/* The structure used for the linked list */
typedef struct Node {
   float value;
   struct Node *next;
} Node;

/* Adds the value to the linked list at the specfied index.
 *
 *   - Nodes in the list will be allocated from the heap.
 *   - When head is NULL a new list is created.
 *   - The index is assumed to be valid - no error handling required.
 *   - When creating a new list (head is NULL) the index will be zero.
 *   - The index will be zero when adding to the front of an existing list.
 *   - The index will be equal to the size of the list when adding to the end.
 *
 * Returns the head of the list.
 */
Node* addAtIndex(Node *head, int index, float value);

/* Gets the specified value from the specified list.
 *
 *   - The head is assumed to be valid - no error handling required.
 *   - The index is assumed to be valid - no error handling required.
 *
 * Returns the value of the specfied node in the list.
 */
float getAtIndex(Node *head, int index);

/* Removes the specified node from the specified list.
 * 
 *   - The head is assumed to be valid - no error handling required.
 *   - The index is assumed to be valid - no error handling required.
 *   - The memory associated with node is freed.
 *   
 * Returns the head of the modified list, NULL if the list has become empty.
 */
Node* removeAtIndex(Node *head, int index);

/* Frees all the memory associated with the list.
 */
void destroyList(Node *head);

#endif
