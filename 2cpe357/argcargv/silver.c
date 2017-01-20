#include <stdio.h>
#include <string.h>
#include "SmartAlloc.h" // #include "SmartAlloc.h" if not on IHS

void PrintArgs(char **args) {
   while (*args)
      printf("%s\n", *args++);
}

void BurnArgs(char **args, int argc) {
   while (argc--) {
      **args = 'X';
      *args++ = NULL;
   }
}


void CopyArgs(char ***dupArgs, char **argv) {      // Base: 4, Surcharge: 0
   int i;                                          
   int count = 0;                                  // Base: 3, Surcharge: 0
                                                   
   while (*argv++) {                               // Base: 5, Surcharge: 1
      count++;                                     // Base: 2, Surcharge: 0
   }                                               
   printf("this is count %d\n", count);                                                
   argv -= count;                                  // Base: 3, Surcharge: 0
   printf("this is argv %s\n", *argv)                                                
                                                   
   *dupArgs = malloc(sizeof(char *) * count--);    // Base: 9, Surcharge: 0                                          
   while(count--) {                  // Base: 13, Surcharge: 2.4
                                                   
                                                   
      (*dupArgs)[count] = malloc(strlen(argv[count]) + 1); // Base: 14, Surcharge: 0
                                                   
      strcpy((*dupArgs)[count], argv[count]);              // Base: 9, Surcharge: 0
                                                   
                                                   
   }                                               
   (*dupArgs)[count+3] = NULL;                           // Base: 6, Surcharge: 0
                                                   
}                                                  



int main(int argc, char **argv) {
   char **dupArgs;
   
   CopyArgs(

&dupArgs, argv);
   BurnArgs(argv, argc);
   PrintArgs(dupArgs);
   printf("Space: %ld\n", report_space());

   return 0;
}