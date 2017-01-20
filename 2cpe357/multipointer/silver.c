#include <stdio.h> 
int main(int argc, char **argv) { 
char **cpp0; 
cpp0 = argv + 1; 
argv[0][5] = argv[1][1] + 1; 
cpp0[1][7] = cpp0[0][1]; 
printf("%s\n", *(argv + 2)); 
*(cpp0 + 1) = *(argv + 1); 
*(argv + 1) = *(cpp0 - 1); 
printf("%s\n", *(cpp0 + 1)); 
*(cpp0 + 1) = *(cpp0 + 1) + 2; 
printf("%s\n", *(cpp0 + 1)); 
*(argv + 2) = *(argv + 1); 
printf("%c %s %s\n", *(argv[1] + 5), *(argv + 1), *(argv + 2)); 
return 0; 
}
