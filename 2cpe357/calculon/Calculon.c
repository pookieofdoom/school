#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
   
   FILE *fp;
   char arg[256];
   char first;
   fp = fopen (argv[1], "r");
   /*
   while (fgets(arg, sizeof(arg), fp)) {
      printf("%s", arg);
   }
   */
   first = fgetc(fp);
   printf("%c\n", first);
   
   fclose(fp);
   
   return 0;
   
   
   
}