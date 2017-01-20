#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

int sum = 0, temp;
char *end;

while(argc-- >1) {
    
      temp = strtol(*argv, &end, 10);
      if(*end) {
         temp = 0;
      }
      
         if(temp) {
               printf("this is atoi %d\n", atoi(*argv));
               sum += temp;
            }   
          

    }


printf("Sum is %d\n", sum);

return 0;
} 
