#include <fcntl.h>
#include <unistd.h>
#include "AltStdio.h"
#include <stdio.h>
ALT_FILE altFiles[NUM_FILES] = {
   {0, altFiles[0].buffer, FILE_READ, 0}, {1, altFiles[1].buffer, 0, BUF_SIZE},
   {2, altFiles[2].buffer, 0, 1}, {-1}, {-1}, {-1}, {-1}, {-1},
   {-1}, {-1}
};

ALT_FILE *altStdin = altFiles+0;
ALT_FILE *altStdout = altFiles+1;
ALT_FILE *altStderr = altFiles+2;

int altPutc(char c, ALT_FILE *fp) {
   *fp->next++ = c;
   if (fp->next == fp->buffer + fp->bufSize)
      altFflush(fp);

   return 0;
}

int altGetc(ALT_FILE *fp) {
   if (fp->next == fp->buffer + fp->bufSize)
      altFflush(fp);
	printf(" altgetc returns  %c\n", fp->flags & FILE_ATEOF ? EOF : *fp->next);  
   return fp->flags & FILE_ATEOF ? EOF : *fp->next++;
}

int altFflush(ALT_FILE *fp) {
   int res;
   printf("   this is fd %d and flag %d and fileread is %d\n", fp->fd, fp->flags, FILE_READ & fp->flags);
   if (fp->fd < 0 || fp->flags & FILE_ATEOF)
      return EOF;
   if (fp->flags & FILE_READ) {
      printf(" im reading\n");
      res = read(fp->fd, fp->buffer + 2, BUF_SIZE);
      printf("hello res is %d\n", res);
      if (res == 0) {

         fp->flags |= FILE_ATEOF;
         
      }
      fp->bufSize = res;
      fp->next = fp->buffer + 2;
   }
   else {
      printf(" im writing\n");
      res = write(fp->fd, fp->buffer, fp->next - fp->buffer);
      fp->next = fp->buffer;
   }
   
   return res < 0 ? EOF : 0;
}