#include <stdio.h>

const int SIZE = 5;
const int NUMVALS = 6;
const int MAX = 31;

int main() {
   int vals = 0;
   short which, newVal;
   char cmd;


   
   while (EOF != scanf(" %c", &cmd)) {
      if (cmd == 'S') {  // Set value
         scanf("%hd %hd", &which, &newVal);
         if (which < 0 || which >= NUMVALS)
            printf("Bad value index %d\n", which);
         else if (newVal < 0 || newVal > MAX )
            printf("Bad value %d\n", newVal);
         else
            

vals = newVal<<which*SIZE | vals & ~(MAX<<which*SIZE)
;
      }
      else if (cmd == 'P') { // Print value
         

which = 0;
            
            while(which <NUMVALS) {
            printf("Value %u is %u\n",which,vals>>(SIZE*which) & MAX);
            which++;

 
         }

      }
   }

   return 0;
}
