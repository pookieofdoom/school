#include <stdlib.h>
#include <stdio.h>
/*
char *cpyStr20(char *str)
{
   int i;
   char cpy[21];
   for (i = 0; str[i] != '\0' && i < 20; i++)
   {
      cpy[i] = str[i];

   }

   cpy[i] = '\0';
   printf("this is copied in the function %s\n", cpy);
   return cpy;

}


int XsquaredPlusY(int X, int Y, int (*f)(float) )
{
   return f(X) + Y;
}

int SQR(float X)
{
   return X * X;
}
*/



int main (int argc, char *argv[])
{
/* char *str = (char *)(int *)malloc(100 * sizeof(int));
   printf("this is size of str %d\n", sizeof(str));
   printf("this is size of *str %d\n", sizeof(*str));

   int nums[5];
   nums[7] = 10;

   char *str = malloc(20);
   scanf("%s", str);
   printf("this is copied %s\n", cpyStr20(str));


   int i = 0;
   while (fork() && i < 5)
   {
      wait(NULL);
      printf("Yo!\n");
      i++;
   }
   printf("%d\n", i);
   return 0;


   int rvalue = EXIT_FAILURE;
   if (argc == 2)
   {
      rvalue = chdir(argv[1]);
   }
   return rvalue;

   int x, y, result = 0;
   printf("Enter the X value that will be squared: ");
   scanf("%d", &x);
   printf("Enter the Y value that will be added to square: ");
   scanf("%d", &y);
   result = XsquaredPlusY(x, y, SQR);
   printf("%d^2 + %d = %d\n", x, y, result);
   return 0;

   char *mode = argv[1];
   char *file = argv[2];
   int oct = strtol(mode, 0, 8);
   chmod(file, oct);
   return 0;
   */

   // pid_t pid1, pid2;
   // int status;
   //
   // printf("Before fork 1\n");
   // pid1 = fork();
   // printf("After fork 1\n");
   //
   // if (!pid1)
   // {
   //    printf("Before fork 2\n");
   //    pid2 = fork();
   //    printf("After fork 2\n");
   //
   //    if (!pid2)
   //    {
   //       printf("Before fork 3\n");
   //       fork();
   //       printf("After fork 3\n");
   //       exit(-1);
   //    }
   //    else
   //    {
   //       wait(&status);
   //       printf("status: %d\n", WEXITSTATUS(status));
   //    }
   // }
   // else
   // {
   //    wait(&status);
   //    printf("status: %d\n", WEXITSTATUS(status));
   // }
   // printf("Done!\n");

   int size = sizeof(unsigned long);
   int size2 = sizeof(int);
   printf("this is size of unsigned long %d\n", size);
   printf("this is size of int %d\n", size2);
   return 0;

}
