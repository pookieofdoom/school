#include <stdio.h>

void SetupAll(int ****ppp, int ***pp, int **p, int *i) {
   *p = i;
   *pp = p;
   *ppp = pp;
   
}


int main() {
   int i = 42, *p, **pp, ***ppp;
   
   SetupAll(&ppp,&pp,&p,&i);
  if (ppp == &pp && pp == &p && p == &i)
      printf("%u %u %u %u\n", ***ppp, **pp, *p, i);
      //printf("%u %u %u %u %u %u\n", ppp,&pp,pp,&p, p, & i);

   return 0;
}