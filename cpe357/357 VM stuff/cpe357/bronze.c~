#include <stdio.h>


/* Accept a count of variadic parameters, followed by that many parameters,
 * which you may assume were passed as char, int, or shorts from main, though
 * they are passed per variadic rules.  Following those is an int * parameter,
 * pointing to a integer onto which you must add the variadic parameters. 
 * (Add the ASCII code in the case of a char.) */
void vaTotal(int num, ...) {
   int *pi, subTot = 0;
   short *ps;
   char *pc;
   int i;

    pi = &num + sizeof(int) * num + sizeof(int) + sizeof(int);
   ps = (short*)(pi + sizeof(int));
   pc = (char *)(pc + sizeof(int));
   subTot = *pi + *ps + *pc;
   printf("subTot is %d\n", subTot);
   pi = (int *)(pc + 1 );
   *pi = subTot;
  
   
}

int main() {
   int i, sum = 42;
   short s;
   char c;
  
   scanf("%d %hd %c", &i, &s, &c);
  
   vaTotal(3, i, s, c, &sum);
  //vaTotal(4, c, c, s, i, &sum);
  
  printf("%d\n", sum);

   return 0;
}
