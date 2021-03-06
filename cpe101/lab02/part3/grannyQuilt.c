#include <stdio.h>
#include <math.h>
#define PI 3.141593
#define BUTTON_COST 2
#define FRINGE_COST 20 


int main (void)
{
   int diameter;
   int fabric_cost;
   int num_people;
   double radius, area, circumference, total_cost, cost_per_person; 

   
   printf("Enter integer diameter of circle in feet: ");
   scanf("%d", &diameter);
   
   printf("Enter fabric cost per square foot in cents: ");
   scanf("%d", &fabric_cost);
   
   printf("Enter number of people sewing: ");
   scanf("%d", &num_people);

   radius = diameter / 2.;
   area = PI * radius * radius;
   circumference = PI * 2 * radius;

   total_cost = ceil( (fabric_cost * area) + (BUTTON_COST * 12 * (radius * 4)) + (FRINGE_COST * circumference));
   cost_per_person = ceil( total_cost / num_people);

   printf("\nThe circle area is %.2f square feet.\n", area);
   printf("The circumference is %.2f feet.\n", circumference);
   printf("Total cost is %.0f cents.\n", total_cost);
   printf("Cost per person is %.0f cents.\n", cost_per_person);
   
   return 0;
}
   
