#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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
   toInsert = 
   


}

int main() {
   int fd, data;

   fd = open("temp.txt", O_CREAT|O_RDWR|O_TRUNC, 0600);
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