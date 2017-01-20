#include <stdio.h>
#include <math.h>

double milesPerGallon(int m, int g);


int main()
{
   int miles;
   int gallons;
   double mpg;
   
   
   printf("Enter the miles driven: ");
   scanf("%d", &miles);
   
   printf("Enter the amount of gallons used: ");
   scanf("%d", &gallons);
   
   mpg = milesPerGallon(miles, gallons);
   
   printf("Your MPG is: %f\n", mpg);
   
   if (mpg >= 30)
   {
      printf("Tree hugging is fun.\n");
   }
   if (mpg < 30 && mpg >= 22)
   {
      printf("You've seen Inconvenient Truth.\n");
   }
   if (mpg <22 && mpg >= 15)
   {
      printf("What's Global Warming??\n");
   }
   if (mpg < 15)
   {
      printf("I think you just ran over a squirrel with your Hummer.\n");
   }
   
   return 0;
  
}



double milesPerGallon(int m, int g)
{
   return (double)m/g;
}