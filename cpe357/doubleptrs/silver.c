#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next; 
} Node;

void ReadList(Node **pHead) {
   int data;
   Node *nd, *temp;  // You may use temp, but don't have to.
      *pHead = NULL;
   temp = *pHead;
   
   
   
   scanf("%d", &data);
   while(data) {
   nd = malloc(sizeof(Node));
      nd->data = data;
      if(!temp) {
        
         temp = nd;
         *pHead = temp;
         
        
      }
      else {
         
         temp->next = nd;
        // nd->next = NULL;
         temp = temp->next;
      }
      
   
   scanf("%d", &data);
   }
}
   
   




void PrintList(Node *head) {
   while (head) {
      printf("%d ", head->data);
	  head = head->next;
   }
   printf("\n");
}

Node **GetFinalPtr(Node **head) {
  
 
  while(*head) {
    
   head= &(*head)->next;
     
   }
     
   return head;
}

void ConcatLists(Node **head1, Node **head2) {
   
   *GetFinalPtr(head1) = *head2;
  
 
  *head2  = NULL;
   
}     

int main() {
   Node *head1, *head2;

   ReadList(&head1);
   ReadList(&head2);
   ConcatLists(&head1, &head2);
   PrintList(head1);
   PrintList(head2);

   return 0;
}