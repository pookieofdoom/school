#include <stdio.h>
#include <math.h>

int getNumber(); 
void displayMessage (int occurrences, int num);

int main()
{
   int number = 0;
   int counter = 0;
   int first = 0;
   int last;
   int findNumber;
   int howmany = 0;

   findNumber = getNumber();
   
   printf("Enter a list of numbers (negative to quit): ");
   scanf("%d", &number);
   
   while ( number >= 0)
   {
      counter = counter +1;
      if (number == findNumber)
      {
         howmany = howmany + 1;
      }
      if (number == findNumber && first == 0)
          {
             first = counter;
             last = first;
          }
       else if( number == findNumber && first !=0)
       {
          last = counter;
       }

   scanf("%d", &number);	  
   }

   printf("\nThis list contains %d numbers.\n", counter);
   if (first ==0)
   {
      displayMessage (howmany, findNumber);
   }
   else
   {
      printf("First occurrence of '%d': %d\n", findNumber, first);
      printf("Last occurrence of '%d': %d\n", findNumber, last);  
      displayMessage(howmany, findNumber);
   }	
   
   return 0;
}   


int getNumber()
{
   int number;
   printf("Enter a number to find: ");
   scanf("%d", &number);
 
   while (number <0)
   {
      printf("Enter a number to find: ");
      scanf("%d", &number);
   }
   return number;
}


void displayMessage (int occurrences, int num)
{
   if (occurrences ==0)
   {
      printf("This list contains no occurrences of %d.\n", num);
   }
   if (occurrences > 10)
   {
      printf("Wow, that's a lot!\n");
   }
   if (occurrences >= 1 && occurrences <=5)
   {
      printf("Not too many in this list.\n");
   }
   if (occurrences > 5 && occurrences <11)
   {
      printf("Quite a few were found!\n");
   } 
}

