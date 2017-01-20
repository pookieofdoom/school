#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
   
  printf("this is argc %d\n", argc);
  if(argc >2 && strcmp(*(argv+1),*(argv+2)) == 0) {
     printf("Equal\n");
  }
  else 
     printf("Not Equal\n");

 
}