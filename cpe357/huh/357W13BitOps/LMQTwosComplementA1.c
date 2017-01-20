#include <stdio.h>
#include <string.h>

void TwosComplement(char *binary)
{
   while (*binary)
   {                  
            *binary++ = *binary == '1' ? '0':'1';
    }
    if (*--binary == '1')
    {
        while (*binary != '0')
        {
            *binary-- = '0';
        }
        *binary = '1';
    }
    else
    {
        *binary = '1';
    }
}    

int main() {
   char number[100];
   
   while (EOF != scanf("%99s", number)) {
      TwosComplement(number);
      printf("%s\n", number);
   }
}
