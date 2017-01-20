#include <stdio.h>
int main(int argc, char **argv) {
   char *cpp0;

   cpp0 = *(argv + 2) + 1;

   printf("%s\n", cpp0);

   cpp0 = argv[0];
   *cpp0 = argv[1][1] + 2;
   printf("%c %s\n", (*argv)[0], cpp0);

   return 0;
}