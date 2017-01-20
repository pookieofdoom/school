#include <stdlib.h>
#include <stdio.h>
#include "SmartAlloc.h"
#include "problem2.h"


Node* addAtIndex (Node* head, int index, float value) {
   Node *temp = malloc(sizeof(Node));
   Node *cur = head;
   temp->value = value;
   int i;
   temp->next = NULL;
   if (!head) {
      head = temp;
      
   }
   else if (head && index == 0) {
      temp->next = head;
      head = temp;
      
   }
   else {
      for(i=0; i<index-1; i++) {
         cur = cur->next;
      }
      temp->next = cur->next;
      cur->next = temp;
         
   }
      
   return head;
}


float getAtIndex(Node *head, int index) {
   Node *cur = head;
   int i;
   for(i=0; i < index; i++) {
      cur = cur->next;
   }
   return cur->value;
}
  

Node *removeAtIndex (Node *head, int index) {
   Node *cur = head;
   Node *temp;
   int i;
   if(!head) {
      return NULL;
   }
   for(i=0; i <index-1; i++) {
      cur = cur->next;
   }
   temp = cur->next;
   cur->next = temp->next;
   free(temp);
   if(index == 0) {
      return NULL;
   }
   return head;
   

}

void destroyList (Node * head) {
   Node *cur = head;
   while(head) {
      cur = cur->next;
      free(head);
      head = cur;
   }
   
  
}
