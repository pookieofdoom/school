#include <stdio.h>
#include "problem2.h"

/* Prototypes for helper functions use for testing */
void printList(const char *label, Node *head, int size);
void checkSpace(int expectedSpace);

int main() {
   Node *head;

   /* Build a list */
   head = addAtIndex(NULL, 0, 9.62);
   head = addAtIndex(head, 1, -7.86);
   head = addAtIndex(head, 2, 8.37);

   /* Check memory use before */
   checkSpace(3 * sizeof(Node));

   /* The test */
   destroyList(head);

   /* Check memory use after */
   checkSpace(0);

   return 0;
}

/* Helper function for testing - displays a list to be checked with diff.
 */
void printList(const char *label, Node *head, int size) {
   int i;

   printf("%s: ", label);

   for (i = 0; i < size - 1; i++)
      printf("%.2f, ", getAtIndex(head, i)); /* <-This calls to YOUR code! */

   printf("%.2f\n", getAtIndex(head, i));
}

/* Helper function for testing - checks memory use in a 32/64-bit agnostic way.
 */
void checkSpace(int expectSpace) {
   int actualSpace = report_space();

   if (actualSpace > expectSpace)
      printf("Too much memory used\n");
   else if (actualSpace < expectSpace)
      printf("Too little memory used\n");
   else
      printf("Expected amount of memory used\n");
}
