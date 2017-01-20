#include <stdio.h>

/* You may NOT call any other string functions.
 * Do NOT include string.h */

int charCount(char w[], char search);

int main ()
{
   char word[10], search;
   int count;

   printf("Word: ");
   scanf("%s", word);
   printf("Character to search for: ");
   scanf(" %c", &search);

   count = charCount(word, search);

   printf("Character Count: %d\n", count);

  return 0;
}

int charCount(char w[], char search)
{
   int i, count=0;
	for (i=0; i<10; i++)
	{
		if (w[i] == search)
		{
			count++;
		}
	}
	return count;
}
