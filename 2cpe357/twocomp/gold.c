#include <stdio.h>
#include <string.h>

#define NUM_SIZE 100
#define DIGIT_ONE '1'
#define DIGIT_ZERO '0'

void TwosComplement(char *number) {                              // Base: 3, Surcharge: 0
   while (*number) {                                             // Base: 4, Surcharge: 3.4
      *number = (*number == DIGIT_ONE) ? DIGIT_ZERO : DIGIT_ONE; // Base: 13, Surcharge: 0
      number++;                                                  // Base: 2, Surcharge: 0
                                                                 
                                                                 
   }                                                             
                                                                 
   if (*--number == DIGIT_ONE) {                                 // Base: 7, Surcharge: 0
      while (*number != DIGIT_ZERO) {                            // Base: 6, Surcharge: 1.6
         (*number--)--;                                          // Base: 4, Surcharge: 0
      }                                                          
      (*number)++;                                               // Base: 3, Surcharge: 0
   }                                                             
   else                                                          // Base: 1, Surcharge: 0
      (*number)++;                                               // Base: 3, Surcharge: 0
}                                                                


int main() {
   char number[100];
   
   while (EOF != scanf("%99s", number)) {
      TwosComplement(number);
      printf("%s\n", number);
   }

   return 0;
}
