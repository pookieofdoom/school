#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartAlloc.h"

#define WORD_LEN 10

/* Write the function PrependStr so that it puts |src| *before* |trg|,
 * and returns a pointer to the resultant string.  Do *not* assume that
 * there is any extra space at the end of |trg|.  Allocate the needed
 * space instead (that's why you need to return a new pointer).  You
 * may use library functions, but NOT REALLOC. Be sure the report_space
 * output matches that of the example executable. This will require 
 * some call of free in PrependStr.
 *
 * DO NOT CHANGE ANY OTHER CODE IN THIS FILE.
 */
char *PrependStr(char *trg, char *src) {
   //char *temp = calloc(sizeof(char), strlen(src) + strlen(trg));
  

   char *temp = calloc(sizeof(char), strlen(src) + strlen(trg) + 1);
   char *ret = temp;
  
   strcpy(temp, src);
   strcat(temp, trg);
   //memmove(temp, src, strlen(src));
   //memmove(temp, trg, strlen(trg));

   //printf("this is temp %s\n", temp);
   free(trg);
   return temp;

   
   
}

int main() {
   char word[WORD_LEN + 1];
   char *sentence = calloc(sizeof(char), 1);

   while (EOF != scanf("%10s", word)) {
      sentence = PrependStr(sentence, " ");
      sentence = PrependStr(sentence, word);
      printf("After %s, space is %d\n", word, report_space());
   }

   printf("%s\n", sentence);
   return 0;
}