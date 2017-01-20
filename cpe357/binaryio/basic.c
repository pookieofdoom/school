#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void printLastChar(int fd) {
char end;
int res ;
lseek(fd,-1,SEEK_END);
res = read(fd, &end, sizeof(char));
printf("Last thing is %c\n", end);

}

int main(int argc, char *argv[]) {
   int fd; 
   char data;

   fd = open("temp.txt", O_CREAT|O_RDWR|O_TRUNC, 0600);
   while (EOF != scanf("%c", &data))
      write(fd, &data, sizeof(char));
      
   printLastChar(fd);  

   close(fd);

   return 0;
}