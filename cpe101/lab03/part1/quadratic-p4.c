#include <stdio.h>
#include <math.h>

double quadratic(double a, double b, double c, char add_or_sub);
double getDouble(char letter);

int main ()
{
   double a,b,c;
   char d, e, f;
   double x1,x2;
   d = 'a';
   e = 'b';
   f = 'c';

   a = getDouble(d);
   b = getDouble(e);
   c = getDouble(f);
   
   x1 = quadratic(a,b,c, 'p');
   x2 = quadratic(a,b,c, 'm');
   if ( pow(b,2) - 4 * a * c < 0)
   {
      printf("This equation has complex roots\n");
   }
   else
   {
      printf("The x-values for this equation are %.3f and %.3f\n", x1,x2); 
   }


   a = getDouble(d);
   b = getDouble(e);
   c = getDouble(f);
   
   x1 = quadratic(a,b,c, 'p');
   x2 = quadratic(a,b,c, 'm');
   if ( pow(b,2) - 4 * a * c < 0)
   {
      printf("This equation has complex roots\n");
   }
   else
   {
      printf("The x-values for this equation are %.3f and %.3f\n", x1,x2); 
   }

   a = getDouble(d);
   b = getDouble(e);
   c = getDouble(f);
   
   x1 = quadratic(a,b,c, 'p');
   x2 = quadratic(a,b,c, 'm');
   if ( pow(b,2) - 4 * a * c < 0)
   {
      printf("This equation has complex roots\n");
   }
   else
   {
      printf("The x-values for this equation are %.3f and %.3f\n", x1,x2);

   }
   return 0;
   
}


double quadratic (double a, double b, double c, char add_or_sub)
{
   double x, root1, root2;
   root1 =(-b + sqrt( pow(b,2) - 4 * a * c)) / (2 * a);
   root2 = (-b - sqrt( pow(b,2) - 4 * a * c)) / (2 * a);
  
   if ( add_or_sub == 'p' )
   {
      x = root1;
   }
   
   else
   {
      x = root2;
   }
   return x;
}

double getDouble (char letter)
{
   double value;
   printf("Enter value %c: ", letter);
   scanf("%lf", &value);
   return value;
   
}
