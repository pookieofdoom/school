#include <stdio.h>
#include <stdlib.h>

#define WORD_LEN 10
#define SENTENCE_LEN 100

/* Fill in ConcatStr so that it concatenates |src| to the end of |trg|
 * You may assume there is enough room at the end of |trg| to do this.
 * No need to allocate or increase the space in |trg|.
 *
 * USE NO [] OPERATORS, NOR ANY LIBRARY FUNCTIONS.  POINTERS ONLY!
 * CHANGE NO CODE IN THIS FILE ASIDE FROM THE CONTENTS OF ConcatStr.
 */
void ConcatStr(char *trg, char *src) {

   char *temp = trg;
   while(*temp != '\0') {
      temp++;
      
   }
   while(*src != '\0') {
      *temp++ = *src++;
   }
}

int main() {
   char word[WORD_LEN + 1];
   char sentence[SENTENCE_LEN + 1] = "";

   while (EOF != scanf("%10s", word)) {
      ConcatStr(sentence, word);
      ConcatStr(sentence, " ");
   }

   printf("%s\n", sentence);
   return 0;
}
