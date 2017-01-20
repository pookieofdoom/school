#include <stdio.h>

#define strchr NOT_ALLOWED
#define strlen NOT_ALLOWED


void TrStr(char *test, char *change) {
   char *temp;
    do{
 
    for(temp = change;*test != *temp && *temp; temp+=2 );

    if(*temp++ )
         *test = *temp;

   
   }
   while(*test++);
}


int main() {
   char str1[20], str2[20], *test = "";

   TrStr(test, "abcd");
   printf("Empty translates to |%s|\n", test);

   while (EOF != scanf("%s %s", str1, str2)) {
      TrStr(str1, "");
      printf("%s -> ", str1);
      TrStr(str1, str2);
      printf("%s\n", str1);
   }
   
   return 0;
}