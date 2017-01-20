#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
   char **ptr;
   
   for (ptr = argv+1; *ptr; ptr++)
      printf("%s ", *ptr);
   printf("\n");

   if (argc > 3) {
      ptr[-1] = NULL;
      argv[1] = argv[0];
      execvp(*argv, argv+1);

   }
   printf("Done!");
      
   return 0;   
}