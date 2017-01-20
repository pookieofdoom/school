/*******************************************************************
 * Starter file for lab quiz 3
 * Name: Anthony Dinh
 * Section: 03
 * By submitting this file, I pledge to have done all my own work
 * and not received help from anyone other than my instructor or TA
 */
#include <stdio.h>

int main()
{
	double sal[10];
	int i;
	for(i=0; i<10; i++)
	{
		printf("Enter salary: ");
		scanf("%lf", &sal[i]);
	}
	printf("Salaries are: \n");
	for (i=0; i<10; i++)
	{
		printf("%10.2f\n", sal[i]);
	}

   return 0;
}
