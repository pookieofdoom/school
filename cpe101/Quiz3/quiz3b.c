/*******************************************************************
 * Starter file for lab quiz 3
 * Name: Anthony Dinh
 * Section: 03
 * By submitting this file, I pledge to have done all my own work
 * and not received help from anyone other than my instructor or TA
 */
#include <stdio.h>

int indexOfLargest (double ar[], int length);

int main()
{
	double sal[10];
	int i, largestIndex;
	int length = 10;

	for(i=0; i<length; i++)
	{
		printf("Enter salary: ");
		scanf("%lf", &sal[i]);
	}
	printf("Salaries are: \n");
	for (i=0; i<10; i++)
	{
		printf("%10.2f\n", sal[i]);
	}

	largestIndex = indexOfLargest (sal, length);
	printf("\nLargest: \n");
	printf("    Index  - %d\n", largestIndex);
	printf("    Salary - %.2f\n", sal[largestIndex]);

   return 0;
}

int indexOfLargest (double ar[], int length)
{
	int i, largestIndex=0;
	double largest=0;
	for (i=0; i<length; i++)
	{
		if (largest < ar[i])
		{
			largest = ar[i];
			largestIndex = i;
		}
	}
	return largestIndex;
}
