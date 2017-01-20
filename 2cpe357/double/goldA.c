#include <stdio.h>
#include "SmartAlloc.h" // #include "SmartAlloc.h" if not on IHS

typedef struct Node {
   int data;
   struct Node *next;
} Node;

/*

while (right node not null) {
 sub-problem: swap one pair
 connect temp to the next node after this sub-problem
 connect the right node to the left node
 connect pHead to the right node->next
 connect the next pointer in the right node (was left) to temp
}
 to iterate: 

 pHead  
 V      
 head----
   V
 A>B>C>D
 ^
 temp

 */

/*
 Termination case:
   either one or zero nodes left then return
   swap the two nodes and return the head correctly

   State:
     head - on return it points to the head of what is downstream
     pHead - pointer to pointer to node - initially it points to head
     Need temp at each level
 */

void SwapPairs(Node **pHead) {
   Node *temp; // temporary pointer to A
   temp = *pHead;
   if (temp && temp->next) { // non-terminal case
      (*pHead) = temp->next->next;
      SwapPairs(pHead); // will change (*pHead) == head
      temp->next->next = *(pHead); // temporarily store address of D in B->next
      *pHead = temp->next; // Point head to B
      temp->next = temp->next->next; // A->next = D
      (*pHead)->next = temp; // B->next = A
   }
}


/*
void SwapPairs (Node **pHead) {
   Node *temp;
   Node *newHead = (*pHead)->next;
   Node **originalPHead = pHead;

   // *pHead = (*pHead)->next
   //temp = first
   //head = 2nd node
   //phead = temp
   // pHead is supposed to be pointing to the first element in next pair
   // pHead->next is supposed to be pointing to the second element in the next pair
   while (*pHead && (*pHead)->next) { // While there are two or more elements
      printf("A\n");
      // sub-problem: swap this pair
      temp = (*pHead)->next->next; // Keep track of the next pair
      printf("B\n");
      (*pHead)->next->next = *pHead; // Point right node to left node
      printf("C\n");
      // Fix it
      (*pHead)->next = temp; // Point the new right node to the next pair
      // Now the two elements are swapped
      printf("D\n");
      pHead = &temp; // Move pHead to the next pair
      printf("E\n");
   }
   printf("F\n");
   //printf("this is head's data %d\n", head->data);
   *originalPHead = newHead;
}
*/

void SwapPairs2(Node **pHead) {
   Node *temp;
   temp = *pHead;
   *pHead = temp->next; // so that head points to b
   while (temp && temp->next) {
      pHead = &(temp->next->next->next); // steps to next pair (points to next in c)
      temp->next->next = temp; // connects b to a
      temp->next = (*pHead); // want to connect a to b
      temp = temp->next; // moves temp to b
   }
   
}

     




int main() {
   Node **data;
   Node *head;
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

   SwapPairs(&head);

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
