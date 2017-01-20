/*******************************************************************
 * Starter file for lab quiz 3
 * Name: Anthony Dinh
 * Section: 03
 * By submitting this file, I pledge to have done all my own work
 * and not received help from anyone other than my instructor or TA
 */
#include <stdio.h>

int indexOfLargest (double ar[], int length);
double calcAvg (double ar[], int length);
int myStrlen (char word[]);

int main()
{
	double sal[10], avg;
	int i, largestIndex;
	int length = 10;
	int wordLength;
	char word[10];

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

	avg = calcAvg (sal, length);
	printf("\nAverage is: %.2f\n", avg);

	printf("Enter a word (max 10 characters): ");
	scanf(" %s", word);
	wordLength = myStrlen (word);
	printf("Length: %d\n", wordLength);
	

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

double calcAvg (double ar[], int length)
{
	int i;
	double sum=0;
	for (i=0; i<length; i++)
	{
		sum = sum + ar[i];
	}
	return sum/length;
}

int myStrlen (char word[])
{
	int i;
	for (i=0; word[i]!=0; i++);
	
	return i;
}
