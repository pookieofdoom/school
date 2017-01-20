#include <stdio.h>
#include <ctype.h>
char quote(char *in) {
printf("\"%s\"\n", in);
}
char cap (char *in) {

   while(*in) {

   putchar(toupper(*in++));
   }
  printf("\n");

}


void GeneralPrint(char *str, char (*f)(char *)) {
    f(str);
}

int main() {

   GeneralPrint("Hello", quote );
   
   GeneralPrint("Hello", cap );
   
   GeneralPrint("World", quote);
   
   GeneralPrint("World", cap);

   return 0;
}
