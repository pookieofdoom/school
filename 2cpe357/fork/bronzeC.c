#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FORKS 5

int main() {
   int i;
   
   for (i = 0; i < FORKS && !fork(); i++) {
      
   fflush(stdout);


      printf("%d ", i);
   }

   

   wait(&i);

 
   printf("\n");

   return 0;
}