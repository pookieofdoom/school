#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Report.h"

#define MAX_FD 3

int main(int argc, char **argv) {
   int timeCounter = 0, outFileNdx = 0, inFileNdx = 0, vFlag = 0;
   int simNum, fdNdx;
   int writeFile[MAX_FD], readFile[MAX_FD];
   Report report; 
   Report avgReport[2]; 

   report.value = 0; 
   while (*++argv) {
   //printf("these are the args %s\n", *argv);
      if (**argv == 'S') {
         timeCounter = atoi(++*argv);
      }

      else if (**argv == 'O') {
         writeFile[outFileNdx] = atoi(++*argv);
         outFileNdx++;
      }

      else if (**argv == 'I') {
         readFile[inFileNdx] = atoi(++*argv);
         inFileNdx++;
      }

      else if (**argv == 'V') {
         report.value = atof(++*argv);
         vFlag = 1;
      }

      else if (**argv == 'D') {
         report.id = atoi(++*argv);
      }
   }

   for (simNum = 0; simNum <= timeCounter; simNum++) {
      report.step = simNum;
      
      for (fdNdx = 0; fdNdx < outFileNdx; fdNdx++) {
         
         if (-1 == write(writeFile[fdNdx], &report, sizeof(Report))) {
            exit(EXIT_FAILURE);
         }

      }

      if (!vFlag) {
         for (fdNdx = 0; fdNdx < inFileNdx; fdNdx++) {

            if (-1 == read(readFile[fdNdx],
             &avgReport[fdNdx], sizeof(Report))) {
               exit(EXIT_FAILURE);
            }
         }

         report.value = (avgReport[0].value + avgReport[1].value) / 2;
      }

   }

   exit(EXIT_SUCCESS);
}
