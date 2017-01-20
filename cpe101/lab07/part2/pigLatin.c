#include <stdio.h>

/* You may NOT call any other string functions.
 * Do NOT include string.h.
 * Do NOT alter main in any way. */

void pigLatin(char w[]);

int main ()
{
   char word[10];

   printf("Word: ");
   scanf("%s", word);

   pigLatin(word);

   printf("Pig Latin Word: %s\n", word);

  return 0;
}

/* Change word to pig latin.
 * Input word will contain at least one character.
 * Don't worry about words that start with a vowel.
 */
void pigLatin(char w[])
{
   int i=0;
	char x;
	x = w[0];
	while(w[i+1] != 0)
	{
		w[i] = w[i+1];
		i++;
	}
	w[i] = x;
	w[i+1] = 'a';
	w[i+2] = 'y';
	w[i+3] = 0;
}
	
		
	
