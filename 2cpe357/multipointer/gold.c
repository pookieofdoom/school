#include <stdio.h> 
int main(int argc, char **argv) { 
char *cpp0; 
char **cpp1; 
cpp0 = *(argv + 2) + 4; 
cpp1 = argv + 2; 
printf("%s\n", cpp0); 
cpp0 = *(cpp1 - 1) + 2; 
argv[0][2] = cpp1[0][1] + 1; 
*(cpp1 - 2) = *(cpp1 - 2) + 3; 
(*(argv + 2))[3] = *(cpp1[-1] + 5); 
*(argv + 2) = *(argv + 2) + 1; 
printf("%s %s\n", *(cpp1 - 2), cpp0); 
return 0; 
} 
