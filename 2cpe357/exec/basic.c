#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   char *firstArg = argv[0];
   if (argc == 1) {
      printf("Done\n");
      return 0;
   }   
   else {
      printf("Not yet...\n");
      

execlp(firstArg ,"blah", NULL);

   }   
   printf("Error\n");
   return 1;
}