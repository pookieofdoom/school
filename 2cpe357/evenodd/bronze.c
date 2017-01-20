#include <stdio.h>
#include "SmartAlloc.h"

typedef struct Node {
   struct Node *next;
   int data;
} Node;

void ReadIntegers(Node **odd, Node **even) {          // Base: 4, Surcharge: 0
   int data;                                          
   Node *temp, *nd;
   Node **head;     
   
   *odd = NULL;                                       // Base: 4, Surcharge: 0
   *even = NULL;                                      // Base: 4, Surcharge: 0
                                
   while (scanf("%d", &data) && data) {               // Base: 10, Surcharge: 14.48
      head = data % 2 ? odd : even; //have head point // Base: 11, Surcharge: 0to the list it belongs to
      nd = calloc (1, sizeof(Node)); //initialize spac// Base: 7, Surcharge: 0e with 0, malloc won't work
      nd->data = data;                                // Base: 3, Surcharge: 0
      if (*head) {                                    // Base: 4, Surcharge: 0
         //use temp node to go down the head list until it reaches the spot it needs to be inserted
         for (temp = *head; temp->next &&             // Base: 15.4, Surcharge: 0
          temp->next->data < data; temp = temp->next) 
            ;                                         
         //insert the node nd                         
         if (temp->data < data) {                     // Base: 5, Surcharge: 0
            nd->next = temp->next;                    // Base: 3, Surcharge: 0
            temp->next = nd;                          // Base: 3, Surcharge: 0
         }                                            
         else {                                       // Base: 1, Surcharge: 0
                                                      
            *head = nd;                               // Base: 4, Surcharge: 0
            nd->next = temp;                          // Base: 3, Surcharge: 0
         }                                            
      }                                               
      else {                                          // Base: 1, Surcharge: 0
         //if null set the head to the new allocated node
         *head = nd;                                  // Base: 4, Surcharge: 0
      }                                               
                                                      
   }                                                  
                                                      
}                               
    


int main() {
   Node *odd, *even;
   Node *temp;
   
   ReadIntegers(&odd, &even);

   temp = odd;
   printf("Odd values:");
   while (temp) {
      printf(" %d", temp->data);
      temp = temp->next;
   }

   temp = even;
   printf("\nEven values:");
   while (temp) {
      printf(" %d", temp->data);
      temp = temp->next;
   }
   printf("\nUsed %d bytes.\n", report_space());

   return 0;
}