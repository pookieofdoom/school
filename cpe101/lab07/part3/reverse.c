#include <stdio.h>
/* You may NOT call any other string functions.
 * Do NOT include string.h.
 * Do NOT alter main in any way. */

void reverseWord(char w[]);

int main ()
{
   char word[10];

   printf("Word: ");
   scanf("%s", word);

   reverseWord(word);

   printf("Reversed: %s\n", word);

  return 0;
}

void reverseWord(char w[])
{
   int i,j;
	char x;
	for (j=0; w[j]!=0; j++);
	
	for(i=0; i<j; i++)
	{
		x = w[i];
		w[i] = w[j-1];
		w[j-1] = x;
		j--;
		
	}
	w[i+j] = 0;
	
}
		
