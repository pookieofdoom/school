/* Starter file for lab quiz1 
 * Name: Anthony Dinh
 * Section: 03
 * By submiting this file, I pledge to have done all my own work
 * and not received help from anyone other than my instructor 
 *
 */

#include <stdio.h>
#include <math.h>

double calcNumPizzas (int numKids, int numAdults);

int main(void)
{
   int kids;
   int adults;
   double cost;
   double totalCost;
   double numPizza;

   printf("How many kids at the party: ");
   scanf("%d", &kids);

   printf("How many adults at the party: ");
   scanf("%d", &adults);

   printf("Cost of each pizza: ");
   scanf("%lf", &cost);
   
   numPizza = calcNumPizzas (kids, adults);
   printf("\nYou need to order %.f pizza(s).\n", numPizza);
   
   totalCost = cost * numPizza;
   printf("This will cost $%.2f.\n", totalCost);

   return 0;
}

double calcNumPizzas (int numKids, int numAdults)
{
   return ceil((1.0 * numKids + 3.0 * numAdults)/8);
}


