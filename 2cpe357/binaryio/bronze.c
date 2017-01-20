#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PERM 0600

void SwapMiddleTwoBytes(int fd) {
   char byte1, byte2;
   
lseek(fd, (lseek(fd, -2, SEEK_END) / 2), SEEK_SET); // Base: 12, Surcharge: 0
read(fd, &byte1, sizeof(char));                         // Base: 6, Surcharge: 0
lseek(fd, 0, SEEK_CUR);                                 // Base: 5, Surcharge: 0
read(fd, &byte2, sizeof(char));                         // Base: 6, Surcharge: 0
                                                    
lseek(fd, -2, SEEK_CUR);                                // Base: 6, Surcharge: 0
write(fd, &byte2, sizeof(char));                        // Base: 6, Surcharge: 0
write(fd, &byte1, sizeof(char));                        // Base: 6, Surcharge: 0



}

int main(int argc, char *argv[]) {
   int fd; 
   char data, c;

   fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, PERM);
   while (EOF != scanf("%c", &data))
      write(fd, &data, sizeof(char));
      
   SwapMiddleTwoBytes(fd);  
   lseek(fd, 0, SEEK_SET);
   while (read(fd, &c, sizeof(char))) {
      printf("%c", c); 
   }   

   printf("\n");

   SwapMiddleTwoBytes(fd);  
   lseek(fd, 0, SEEK_SET);
   while (read(fd, &c, sizeof(char))) {
      printf("%c", c); 
   } 

   close(fd);

   return 0;
}