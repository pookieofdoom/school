#include <stdio.h>
#include "SmartAlloc.h" // #include "SmartAlloc.h" if not on IHS

typedef struct Node {
   int data;
   struct Node *next;
} Node;

Node *SwapPairs(Node *head) {
   Node *cur = head, *next, *temp;

   

if(head ) {
   head = head->next;         // Base: 3, Surcharge: 0
   temp = NULL;
}

                           
while (cur && cur->next) { // Base: 5, Surcharge: 4.8
   next = cur->next;       // Base: 3, Surcharge: 0
   cur->next = next->next; // Base: 3, Surcharge: 0
   next->next = cur;       // Base: 3, Surcharge: 0
                           
                           
   if (temp)               // Base: 3, Surcharge: 0
      temp->next = next;   // Base: 3, Surcharge: 0
   temp = cur;             // Base: 3, Surcharge: 0
   cur = cur->next;        // Base: 3, Surcharge: 0
                           
                           
}                          
                           
                           
return head;               // Base: 11, Surcharge: 0


}

int main() {
   Node **data;
   Node *head, *temp;
   int i, size;

   scanf("%d", &size);  
   
   if (size) {
      data = calloc(sizeof(Node *), size);
   }
   else {
      data = NULL;
   }

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

   if (data) {
      head = data[0];
   }
   else {
      head = NULL;
   }

   head = SwapPairs(head);

   // Print in Node-Order
   printf("In Node Order: ");
   while (head) {
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