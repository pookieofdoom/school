#include <stdio.h>

int main() {
  


  stderr = stdout;
  printf("Line start");
  fprintf(stderr, " middle ");
  printf("line end\n");

  return 0;
}