#include <stdio.h>
#include <SmartAlloc.h>


void readAndPrintDoubles(double *d1, double *d2) {
d1 = malloc(sizeof(double));
d2 = malloc(sizeof(double));
scanf("%lf%lf", d1 , d2);
printf("%.1f %.1f\n", *d1, *d2);
free(d1);
free(d2);
}



int main() {
   double *d1 = NULL, *d2 = NULL;

   readAndPrintDoubles(d1, d2);

   printf("Final space: %d\n", report_space());

   return 0;
}
