#include <stdio.h>

void g() {
int a;
a++;
}


void f(int **p) {
   int i1 = 42;
   
   *p = &i1;
}

int main() {
   int *i, *j, *k;

   f(&i);
   f(&j);
   f(&k);
   g();
   printf("%d %d %d\n", *i, *j, *k);
   
   return 0;
}