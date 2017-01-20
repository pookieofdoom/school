#include <stdio.h>
#include <string.h>

int main()
{
	int n, m=1;
	char M[100] = "if you really want to part with me";
	char N[100] = "put your hands where my eyes could see";
	for (n=0;n<strlen(N); n++)
	{
		if(M[n] ==m)
		{
			M[n] = 'M';
		}
		if (N[n] == m)
		{
			N[n] = 'M';
		}
	}
	printf("%s  %s\n", M, N);
	return -1;
}