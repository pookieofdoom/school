/* CPE 101 Lab 4
   Anthony Dinh
*/
#include <stdio.h>

/* function prototypes */
int get_table_size();
int get_first();
int get_increment();
void show_table(int size, int first, int increment);

int main(void)
{
   int table_size;
   int first;
   int increment;
	  
   /* loop until sentinel is reached */
   table_size = get_table_size();
   while (table_size != 0)
   {
      first = get_first();
      increment = get_increment();
      show_table(table_size, first, increment);
      table_size = get_table_size();
   }
	return 0;
}

/* Obtain a valid table size from the user */
int get_table_size()
{
   int size;
   printf("Enter number of rows in table (0 to end): ");
   scanf("%d", &size);
   while (size < 0)
   {
      printf("Size must be non-negative.\n");
      printf("Enter number of rows in table (0 to end): ");
      scanf("%d", &size);
   }
   return size;
}

/* Obtain the first table entry from the user */
int get_first()
{
   int first;
   printf("Enter the value of the first number in the table: ");
   scanf("%d", &first);
   while (first < 0)
   {
      printf("First must be non-negative.\n");
      printf("Enter the value of the first number in the table: ");
      scanf("%d", &first);
   }

   return first;
}

int get_increment()
{
   int number;
   printf("Enter the increment between rows: ");
   scanf("%d", &number);
   while (number < 0)
   {
      printf("Increment must be non-negative.\n");
      printf("Enter the increment between rows: ");
      scanf("%d", &number);
   }
   return number;
} 

/* Display the table of cubes */
void show_table(int size, int first, int increment)
{
   int x;
   int sum = 0;

   
   printf("A cube table of size %d will appear here starting with %d.\n", 
    size, first);
   printf("Number  Cube\n");
   /* Insert counting loop here */ 
   for (x=0; x < size; x = x +1)
   {
      int cube;
      cube = first * first * first;
	  if (x < size)
	  {
         printf("%-6d  %d\n", first, cube);
		 first = first + increment;
		 sum = sum + cube;
	  }
	     
   }
   printf("\nThe sum of cubes is: %d\n\n", sum);
}
