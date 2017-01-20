/* CPE 101 Lab 4
   Your Name
*/
#include <stdio.h>

/* function prototypes */
int get_table_size();
int get_first();
void show_table(int size, int first);

int main(void)
{
   int table_size;
   int first;
	  
   /* loop until sentinel is reached */
   table_size = get_table_size();
   while (table_size != 0)
   {
      first = get_first();
      show_table(table_size, first);
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

   return first;
}

/* Display the table of cubes */
void show_table(int size, int first)
{
   printf("A cube table of size %d will appear here starting with %d.\n", 
    size, first);
   printf("Number  Cube\n");
   /* Insert counting loop here */ 
   printf("\nThe sum will appear here.\n\n");
}
