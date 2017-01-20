#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  //printf("%s ", *++argv);
  char *init = argv[0];
  char *test = *++argv;

  printf("%s\n", test);
  execlp("./Cell", NULL);
  return 0;


}