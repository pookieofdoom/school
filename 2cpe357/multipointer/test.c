#include <stdio.h>
int main(int argc, char **argv) {
   char *cpp0;

   cpp0 = *(argv + 1) + 1;

   argv[2][1] = argv[1][0];
   *(*argv + 2) = *argv[0];
   *(argv + 2) = *(argv + 2) + 4;
   (*argv)[3] = (*argv)[6] + 2;
   *(argv + 1) = *argv + 2;
   printf("%s %s %s %s\n", argv[0] + 1, *(argv + 1), *(argv + 2), cpp0);

   return 0;
}