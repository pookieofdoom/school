#include "problem1.h"
#include <stdio.h>
#include <stdlib.h>

char *prepend (const char *str,const char *prefix) {
   char *temp = malloc(sizeof(char));
   int i = 0;
   int j = 0;
   while(*(prefix+i)!= '\0'){
      *(temp+i) = *(prefix+i);
      i++;
   }
   while(*(str+j)!= '\0'){
      *(temp+i) = *(str+j);
      j++;
      i++;
   }
   return temp;
}
   
   
