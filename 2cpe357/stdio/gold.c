#include "AltStdio.h"

int main() {
   int v1, v2, v3;
   printf("EOF IS %d\n", EOF);
   v1 = altGetchar();
   v2 = altGetchar();
   while (EOF != (v3 = altGetchar())) {
      altPutchar(v1);
      altPutchar(v2);
      altPutchar(v3);
      printf("this is altUngetc v1 %d \n", altUngetc(v1, altStdin));
      
      printf("the next is %c v1 is %c\n", *altStdin->next, v1);
      printf("this is altUngetc v2 %d\n", altUngetc(v2, altStdin));
     printf("the next is %c v2 is %c\n", *altStdin->next, v2);
      v1 = altGetchar();
      v2 = altGetchar();
   }
   altFflush(altStdout);

   return 0;
}