#include <stdio.h>
int main(int argc, char **argv) {
   char *cpp0;
   char *cpp1;

   cpp0 = *(argv + 2) + 2;
   printf("this is cpp0 %s\n", cpp0);
   cpp1 = cpp0 - 1;

   argv[1][5] = argv[0][6] + 1;
   printf("%c\n", argv[1][5]);

   argv[1][5] = argv[1][5] + 2;
   argv[1][4] = **argv;
   printf("%s %s %s\n", *(argv + 1) + 2, cpp0, cpp1);

   return 0;
}