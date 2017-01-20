#include <stdio.h>

#define NUM_LETTERS 26
#define MAX_MESSAGE 100
#define CAPITAL_A 'A'

void encrypt(char *message, int shift) {
   while(*message != '\0'){ 
     if(*message +shift > 'Z') 
         *message -= NUM_LETTERS - shift;
      
     else
         *message += shift;
     message++;
   }
     
}


int main() {
   char message[MAX_MESSAGE];
   int shift;

   scanf("%s", message);
   scanf("%d", &shift);

   encrypt(message, shift);

   printf("%s\n", message);

   return 0;
}