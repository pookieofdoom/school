#include <stdio.h>
#include <math.h>

double distance(double x1, double y1, double x2, double y2);

int main ()
{
   double x1, y1, x2, y2, dist;

   printf("Enter x1: ");
   scanf("%lf", &x1);
   
   printf("Enter y1: ");
   scanf("%lf", &y1);
   
   printf("Enter x2: ");
   scanf("%lf", &x2);
   
   printf("Enter y2: ");
   scanf("%lf", &y2);

   dist = distance (x1, y1, x2, y2);
   printf("The distance between (%.2f, %.2f) and (%.2f, %.2f) is %.2f\n", x1, y1, x2, y2, dist);

   return 0;
}


double distance (double x1, double y1, double x2, double y2)
{
   double dist;
   dist = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
   return dist;
}
