#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next;
} Node;

Node *SwapPairs(Node *head) {
   Node **node, *temp;
	node = &head;
	head = head->next;
	head->next = *node;
	(*node)->next = NULL;
	

   return head;
}

int main() {
   Node **data;
   Node *head, *temp;
   int i, size;

   scanf("%d", &size);
   data = malloc(sizeof(Node *) * size);
   // Read in data
   for (i = 0; i < size; i++) {
      data[i] = malloc(sizeof(Node));
      scanf("%d", &data[i]->data);

   }   

   //Set up linked list
   for (i = 0; i < size; i++) {
      if (size - 1 == i) {
         data[i]->next = NULL;
      }   
      else {
         data[i]->next = data[i + 1]; 
      }   
   }   

   head = data[0];

   head = SwapPairs(head);

   // Print in Node-Order
   printf("In Node Order: ");
   while(head) {
      printf("%d ", head->data);
      head = head->next;
   }
   printf("\n");

   // Print in List-Order
   printf("In List Order: ");
   for (i = 0; i < size; i++) {
      printf("%d ", data[i]->data);
   }
   printf("\n");

   return 0;
}