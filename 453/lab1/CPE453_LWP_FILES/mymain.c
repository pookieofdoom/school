#include <stdio.h>
#include <stdlib.h>
#include "lwp.h"


void myfunc(int x) {
   int i;
   for (i = 0; i< x; i++) {
      printf("value is %d\n", x);
      if (i == 0)
      {
         lwp_stop();
         printf("did i ever continue\n");
      }


   }

}

int AlwaysZero() {
  /* A scheduler that always run the first one */
  return 0;
}

int main () {
   //lwp_set_scheduler(AlwaysZero);
   new_lwp((lwpfun)myfunc, (void*)10, 2048);
   new_lwp((lwpfun)myfunc, (void*)3, 2048);
   new_lwp((lwpfun)myfunc,(void*)4, 2048); 
   
   lwp_start();
   printf("1st stop\n");
   lwp_start();
   printf("2nd stop\n");
   lwp_start();
   exit(1);
}