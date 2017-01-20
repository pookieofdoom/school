#include <stdio.h>

#define strchr NOT_ALLOWED
#define strlen NOT_ALLOWED





  void TrStr(char *str1, char *str2){

     char *temp = str2;
     while(*str1 != '\0') {
        
        while(*str2 != '\0') {
           if(*str1 == *str2) {
           *str1 = *(str2 + 1);
           break;
         }
         str2+=2;
         }
        str1++;
        str2 = temp;
        }
      


  }







int main() {
char str1[20], str2[20], *test = "";


while (EOF != scanf("%s %s", str1, str2)) {

TrStr(str1, str2);
printf("%s\n", str1);
}

return 0;
}
