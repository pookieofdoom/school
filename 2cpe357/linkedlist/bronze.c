#include <stdio.h>
#include <stdlib.h>
#include "SmartAlloc.h"

typedef struct Node {
   int data;          // Could put any kind of data here
   struct Node *next; // Self-referential requires "struct"
} Node;

// Insert a new node as the second one on the list, if there is already a node, or 
// as the only node on the list, otherwise.
Node *AddSecond(Node *head, int data) {
   Node *temp;
   temp = malloc(sizeof(Node));
   temp->data = data;
   temp->next = NULL;
   if(head) {
      temp->next = head->next;
      head->next = temp;
      
   }
   else
      head = temp;
   return head;
}

   void PrintAll(char *tag, Node *head) {
      Node *temp;
      
      printf("%s:", tag);
      for (temp = head; temp != NULL; temp = temp->next)
      printf(" %d", temp->data);
      printf("\n");
   }

   int main() {
      Node *head = NULL;
      int val;
      
      while (EOF != scanf("%d", &val))
      head = AddSecond(head, val);
      PrintAll("After insert", head);

      return 0;
   }