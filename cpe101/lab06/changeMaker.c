#include <stdio.h>


int bills(double paid, double price, int *twenties, int *tens, int *fives, int *ones);
void coins (int change, int *quarters, int *dimes, int *nickels, int *pennies);
int main()
{
   double price;
   int paid, numBill,total, change;
   int twenty,ten,five,one,quarter,dime,nickel,penny;
   printf("Enter amount due for merchandise: ");
   scanf("%lf", &price);
   printf("Enter denomination of bills used for payment: ");
   scanf("%d", &paid);
   while (paid != 1 && paid != 5 && paid != 10 && paid != 20)
   {
      printf("Enter denomination of bills used for payment: ");
      scanf("%d", &paid); 
   }
   printf("Enter number of bills of this denomination: ");
   scanf("%d", &numBill);
   if (paid * numBill < price)
   {
      printf("Your payment is insufficient!\n");
	  printf("Enter denomination of bills used for payment: ");
	  scanf("%d", &paid);
	  while (paid != 1 || paid != 5 || paid != 10 || paid != 20)
      {
         printf("Enter denomination of bills used for payment: ");
         scanf("%d", &paid); 
      }
 	     printf("Enter number of bills of this denomination: ");
         scanf("%d", &numBill);
   }
   total = paid * numBill;
   printf("\nChange should be\n");
   change = bills(total, price, &twenty, &ten, &five, &one);
   if(twenty >0)
   {
      printf("%d 20 dollar bill(s)\n", twenty);
   }
   if(ten >0)
   {
      printf("%d 10 dollar bill(s)\n", ten);
   }
   if(five >0)
   {
      printf("%d 5 dollar bill(s)\n", five);
   }
   if(one >0)
   {
      printf("%d 1 dollar bill(s)\n", one);
   }
   coins(change, &quarter, &dime, &nickel, &penny);
  if (quarter >0)
   {
      printf("%d quarters\n", quarter);
   }
   if (dime >0)
   {
      printf("%d dimes\n", dime);
   }
   if (nickel >0)
   {
      printf("%d nickels\n", nickel);
   }
   if (penny >0)
   {
      printf("%d pennies\n", penny);
   }
   
   
   return 0; 
}

int bills(double paid, double price, int *twenties, int *tens, int *fives, int *ones)
{
   int change;
   change = paid - price;
   
   *twenties = change/20;
   change = change%20;
   *tens = change/10;
   change = change%10;
   *fives = change/5;
   change = change%5;
   *ones = change/1;
   change = change%1;
   
   return (((paid-price) - (int)(paid-price)) * 100) + 0.5;
}

void coins (int change, int *quarters, int *dimes, int *nickels, int *pennies)
{
   *quarters = change/25;
   change = change%25;
  *dimes = change/10;
   change = change%10;
   *nickels = change/5;
   change = change%5;
   *pennies = change/1;
   change = change%1;
   
 }
