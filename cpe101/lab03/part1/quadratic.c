#include <stdio.h>
#include <math.h>

double quadratic(double a, double b, double c);
double getDouble(char letter);

int main ()
{
   double a,b,c;
   char d, e, f;
   double x;
   d = 'a';
   e = 'b';
   f = 'c';

   a = getDouble(d);
   b = getDouble(e);
   c = getDouble(f);
   
   x = quadratic(a,b,c);
   printf("One x-value for this equation is %.3f\n", x); 

   a = getDouble(d);
   b = getDouble(e);
   c = getDouble(f);

   x = quadratic(a,b,c);
   printf("One x-value for this equation is %.3f\n", x);

   a = getDouble(d);
   b = getDouble(e);
   c = getDouble(f);
   
   x = quadratic(a,b,c);
   printf("One x-value for this equation is %.3f\n", x); 


   return 0;
   
}


double quadratic (double a, double b, double c)
{
   double x;
   x = (-b + sqrt( pow(b,2) - 4 * a * c)) / (2 * a);
   return x;
}

double getDouble (char letter)
{
   double value;
   printf("Enter value %c: ", letter);
   scanf("%lf", &value);
   return value;
   
}
