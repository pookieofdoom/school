#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartAlloc.h"

void printArgs(char **args) {

   while (*args) {
  
      printf("%s\n", *args++);
    
      }
}

void burnArgs(char **args, int argc) {
   while (argc--) {
      **args = 'X';
      *args++ = NULL;
   }
}

void copyArgs(char ***dupArgs, char **argv) {
   int i;
   int count = 0;
   
   while(*argv++) {
    count++;
    }
   
    argv -= count;

     
   *dupArgs = malloc(sizeof(char*) * count--);

   while(*argv) {

   **dupArgs = malloc(strlen(*argv) +1);
  printf("%s \n", **dupArgs);
   
   strcpy(**dupArgs, *argv++);
    printf("%s \n", **dupArgs);
  
   
   }
   
  **dupArgs = NULL;
  **dupArgs -=count;

}
/* void copyArgs(char ***dupArgs, char **argv) {
   int i;
   int count = 0;
   
   while(*argv++) {
    count++;
    }
   
    argv -= count;

     
   *dupArgs = malloc(sizeof(char*) * count--);
 
   for(i=0; i<count; i++){
   
   
   (*dupArgs)[i] = malloc(strlen(argv[i]) +1);
   
   strcpy((*dupArgs)[i], argv[i] );
   printf("hiii %s\n", (*dupArgs)[i]);
 
   }
  (*dupArgs)[i] = NULL;

} */


int main(int argc, char **argv) {
   char **dupArgs;
   
   copyArgs(&dupArgs, argv);
  
  
  burnArgs(argv, argc);

   
   printArgs(dupArgs);
   printf("Space: %d\n", report_space());

   return 0;
}