#include <stdio.h>
#include <ctype.h>


void reverse(char *begin, char *end)
{
  char temp;
  while (begin < end)
  {
    temp = *begin;
    *begin++ = *end;
    *end-- = temp;
  }
}


	
void ReverseWords(char *string)
{
	char *begin = string;
	char *end = string;
 
	while( *end )
	{
		end++;
		if (!isalpha(*end))
		{
			reverse(begin, end-1);
			begin = end+1;
			while ( *begin && !isalpha(*begin) )
			{
				begin++;
			}
			end = begin;
		}
	}   
}  

int main() {
   char line[100];
   
   while (fgets(line, 100, stdin)) {  // Reads a line at a time into line.
      ReverseWords(line);
      printf("%s\n", line);
   }
}