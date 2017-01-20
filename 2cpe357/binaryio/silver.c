#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define PERM 0600

/*
void InsertSort(int vals[], int size) {
   int ndx, insNdx, toInsert;

   for (ndx = 1; ndx < size; ndx++) {
      toInsert = vals[insNdx = ndx];
      while (insNdx > 0 && toInsert < vals[insNdx-1]) {
         vals[insNdx] = vals[insNdx-1];
         insNdx--;
      }
      vals[insNdx] = toInsert;
   }
}
*/

void FileSort(int fd) {
   size_t ndx, limit;
   int toInsert, temp;

   

   
   for (limit = sizeof(int); limit < lseek(fd, 0, SEEK_END); limit += sizeof(int)) {

      lseek(fd, limit, SEEK_SET);
      read(fd, &toInsert, sizeof(int));

      for (ndx = limit; ndx > 0; ndx -= sizeof(int)) {
         lseek(fd, ndx - sizeof(int), SEEK_SET);
         read(fd, &temp, sizeof(int));
 
         if (toInsert < temp) {
            lseek(fd, ndx - sizeof(int), SEEK_SET);
            write(fd, &toInsert, sizeof(int));
            write(fd, &temp, sizeof(int));
         }
      }
      
   }
     
   


}

int main() {
   int fd, data;

   fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, PERM);
   while (EOF != scanf("%d", &data))
      write(fd, &data, sizeof(int));

   FileSort(fd);

   lseek(fd, 0, SEEK_SET);
   while (0 != read(fd, &data, sizeof(int)))
      printf("%d ", data);
   printf("\n");

   close(fd);

   return 0;
}