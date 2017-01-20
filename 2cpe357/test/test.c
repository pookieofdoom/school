#include <stdio.h>

#define strchr NOT_ALLOWED
#define strlen NOT_ALLOWED

void TrStr(char *str1, char *str2) {
   char *temp;
   do {
      for(temp = str2; *str1 != *temp && *temp; temp +=2)
      
         if(*temp++)
            *str1 = *temp;
         
      
   }
   while(*str1++);
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