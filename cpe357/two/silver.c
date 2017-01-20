#include <stdio.h>
#include <string.h>


void TwosComplement(char  *number) {
    int len = strlen(number);
    int i,j;
    for(i=len-1; i>=0; i--) {
      if(number[i] == '1')
        break;

    }
    for(j=0; j<i;j++)
     {
        if(number[j] == '0')
          number[j] = '1';
        else
          number[j] = '0';
    }
}


int main() {
   char number[100];
   
   while (EOF != scanf("%99s", number)) {
      TwosComplement(number);
      printf("%s\n", number);
   }

   return 0;
}