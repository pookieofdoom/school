#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
   
   int sum = 0, temp;
   char *end;
   
        while(*++argv != NULL) {
         temp = 1;
         printf("dsad\n");
         for(end = (*argv+1); *end != '\0' ; end++) {
          printf("%c\n", *end);
           if(*end < '0' || *end > '9' ) {
               printf("%c\n", *end);
               printf("her?\n");
               temp = 0;
             }  
            
      }
         if(temp) {
               
               sum += atoi(*argv);
            }   
          

    }


    

  

   


   printf("Sum is %d\n", sum);

   return 0;
}