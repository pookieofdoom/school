
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "AltStdio.h"
#include <stdio.h>
//#define printf ERROR
#define fprintf ERROR

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

   return -1;
}

int altFflush(ALT_FILE *fp) {
   int res;
   
   if (fp->fd < 0 || fp->flags & FILE_ATEOF)
      return EOF;

   if (fp->flags & FILE_READ) {
      res = read(fp->fd, fp->buffer, BUF_SIZE);
      if (res == 0)
         fp->flags |= FILE_ATEOF;
      fp->bufSize = res;
   }
   else
      res = write(fp->fd, fp->buffer, fp->next - fp->buffer);
     
   fp->next = fp->buffer;
   return res < 0 ? EOF : 0;
}
#define getVAInt(p) va_arg(p, int)
#define getVAStr(p) va_arg(p, char *)

int altFprintf(ALT_FILE *fp, char *fmt, ...) {
   va_list params;
   va_start(params, fmt);
   char *string, iVal[10];
   unsigned int ndx, value, count = 0, temp;
   
   while (*fmt) {
      if (*fmt == '%' ) {
      
         switch (*++fmt) {
         
         case 'c':
            altPutc(getVAInt(params), fp);
            break;
         case 'i':
            
            value = getVAInt(params);
            ndx = 9;
            do {
               iVal[ndx--] = '0' + value % 10;
               value /= 10;
            } while (value > 0);
            
            while (ndx < 9)
               altPutc(iVal[++ndx], fp);
            break;
         case 's':
           // printf("hi\n");
            string = getVAStr(params);
            while (*string)
               altPutc(*string++, fp);
            break;
         case '*':
           
            value = getVAInt(params);
            
            //printf("derp  is %d\n", value);
              
              *fmt++;
               if(*fmt == 'c') {
                
                   while( value > 1) {
                  altPutc(' ' , fp);
                  value--;
               }
                  altPutc(getVAInt(params), fp);
                  break;
               
               }
               if(*fmt == 'i') {
               
                  temp = value;
                  value = getVAInt(params);
                  
                  ndx = 9;
                  do {
                     iVal[ndx--] = '0' + value % 10;
                     value /= 10;
                     count++;
                  } while (value > 0);
                 while(temp > count) {
                     altPutc(' ', fp);
                     temp --;
                  }
                 while (ndx < 9)
                  altPutc(iVal[++ndx], fp);
                  break;
              }
                if(*fmt == 's') {
                
                     string = getVAStr(params);
                   
                 while( value > strlen(string)) {
                  altPutc(' ' , fp);
                  value--;
               }
                   while (*string)
                     altPutc(*string++, fp);
                  break;
               }
            
           break;

         default:
            altPutc('%', fp);
            altPutc(*fmt, fp);
         }
      }
      else
         
         altPutc(*fmt, fp);
      fmt++;
   }
   return 1;  // No one checks this anyway.
}
