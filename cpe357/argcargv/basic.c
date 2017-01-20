#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
   
   if(argc <=2 || strcmp(argv[0], argv[1]) !=0){
  
printf("Not Equal\n");
}
else {
printf("Equal\n");
}
   return 0;
}