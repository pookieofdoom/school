#include <stdio.h>
#include <string.h>

#define LENGTH_LIMIT 10

void Login() {
   char username[LENGTH_LIMIT];
   char password[LENGTH_LIMIT];
   memset(username, 0, LENGTH_LIMIT);
   memset(password, 0, LENGTH_LIMIT);
// printf("%d %d\n", &temp, &Login);
   scanf("%9s", username);
   scanf("%9s", password);
   printf("%d %d\n", username, password);
}

void ObtainInfo() {
 
  char bob[LENGTH_LIMIT]; //= Login();
   char pop[LENGTH_LIMIT-1];
   printf("%s %s \n", &bob, &pop);

}



int main() {
   Login();
   ObtainInfo();
   printf("%d %d \n", &Login, &ObtainInfo);
   return 0;
}