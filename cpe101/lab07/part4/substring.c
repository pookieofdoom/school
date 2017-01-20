#include <stdio.h>

/* You may NOT call any other string functions.
 * Do NOT include string.h.
 * Do NOT alter main in any way. */

int hasSubstring(char w[], char sub[]);

int main ()
{
   char word[10], substring[10];

   printf("Word: ");
   scanf("%s", word);
   printf("Substring to search for: ");
   scanf("%s", substring);

   if (hasSubstring(word, substring))
   {
      printf("%s contains the substring %s.\n", word, substring);
   }
   else
   {
      printf("%s does NOT contain the substring %s.\n", word, substring);
   }

   return 0;
}

int hasSubstring(char w[], char sub[])
{
   int i,j,x=1;
	int c;
	for (i=0; w[i]!=0; i++)
	{
		if(sub[0]==w[i])
		{
			c= i+1;
			for(j=1; sub[j]!=0; j++)
			{
				if(sub[j] == w[c])
				{
					x = 1;
					c++;
				}
				else
				{
					x=0;
					break;
				}
				
			}
			if (x==1)
			{
				return 1;
			}
		}
	}
	
	return x;
}
		

