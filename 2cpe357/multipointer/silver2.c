#include <stdio.h> 
int main(int argc, char **argv) 
{ char *cpp0; 
cpp0 =  *argv + 2; 
printf("this is cpp0 %s\n", cpp0);
*(cpp0 + 1) = argv[1][3] + 2; 
*argv = *(argv + 2);
 *cpp0 = *(cpp0 + 1); 
 *(*(argv + 2) + 3) = *argv[1]; *
 (cpp0 + 3) = *(cpp0 + 1); 
 printf("%s\n", cpp0); 
 return 0; 
 }
