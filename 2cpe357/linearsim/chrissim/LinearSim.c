#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Report.h"

#define MAXARGS 7
#define MAXCELLS 50

void CloseParentCells(int rightCell[], int leftCell[], int prevLeftCell[], 
 int prevRightCell[]) {
   close(prevLeftCell[0]);
   close(prevRightCell[0]);
   close(prevLeftCell[1]);
   close(prevRightCell[1]);

   prevRightCell[0] = rightCell[0];
   prevRightCell[1] = rightCell[1];
   prevLeftCell[0] = leftCell[0];
   prevLeftCell[1] = leftCell[1];
}

void CloseChildCells(int rightCell[], int leftCell[], int prevLeftCell[], 
 int prevRightCell[]) {

   close(prevLeftCell[0]);
   close(prevRightCell[0]);
   close(prevRightCell[1]);
   close(leftCell[0]);
   close(rightCell[1]);
}

void PreForkClose(int rightCell[], int leftCell[], int parentPipe[]) {

   close(parentPipe[0]); 
   close(leftCell[1]);
   close(rightCell[0]);
}

int PipeMe(int numCells, int numSteps, double left, double right, pid_t pid[]) {
   int parentPipe[2] = {-1, -1}, rightCell[2] = {-1, -1}, leftCell[2] =
    {-1, -1}, prevLeftCell[2] = {-1, -1}, prevRightCell[2] = {-1, -1}, 
    initCells, counter = 0;
   char stepArg[MAXARGS], idArg[MAXARGS], outArg1[MAXARGS], outArg2[MAXARGS], 
    outArg3[MAXARGS], inArg1[MAXARGS], inArg2[MAXARGS], value[MAXARGS];

   pipe(parentPipe);
   for (initCells = 0; initCells < numCells; initCells++) {
      pipe(leftCell);
      pipe(rightCell);

      if (!(pid[counter++] = fork())) {
         PreForkClose(rightCell, leftCell, parentPipe);
         sprintf(stepArg, "S%d", numSteps);
         sprintf(idArg, "D%d", initCells);
         sprintf(outArg1, "O%d", parentPipe[1]);
         outArg3[0] = value[0] = outArg2[0] = 0;
         
         if (initCells == numCells - 1 && numCells != 1) {
            CloseChildCells(rightCell, leftCell, prevLeftCell, prevRightCell);
            if (numCells == 2) {
               close(prevLeftCell[1]);
            }
            else {
               sprintf(outArg2, "O%d", prevLeftCell[1]);
            }
            sprintf(value, "V%f", right);
         } 
         else if (!initCells) {
            close(leftCell[0]);
            sprintf(value, "V%f", left);
            if (numCells <= 2) {
               close(rightCell[1]);
            } 
            else {
               sprintf(outArg2, "O%d", rightCell[1]);
            }
         }
         else {
            close(prevRightCell[1]);
            close(prevLeftCell[0]);
            sprintf(inArg1, "I%d", leftCell[0]);
            sprintf(inArg2, "I%d", prevRightCell[0]);

            if (initCells == 1) {
               close(prevLeftCell[1]);
            }
            else {
               sprintf(outArg3, "O%d", prevLeftCell[1]);
            }
            if (initCells == numCells - 2) {
               close(rightCell[1]);
               outArg2[0] = 0;
            }
            else {
               sprintf(outArg2, "O%d", rightCell[1]);
            }
         }
         execlp("./Cell", "./Cell", stepArg, idArg, value, outArg1, 
          outArg2, outArg3, inArg1, inArg2, NULL);
      }
      else {
         CloseParentCells(rightCell, leftCell, prevLeftCell, prevRightCell);
      }
   }
   close(parentPipe[1]);
   return parentPipe[0];
}

int main(int argc, char **argv) {
   Report cell;
   int numSteps = -1, numCells = -1, parentPipe, status, exited = 0,
    counter, cellReports[MAXCELLS], fewReports = 0, manyReports = 0;
   pid_t pid[MAXCELLS];
   double left = 0.0, right = 0.0;

   while (*++argv) {
      if (**argv == 'C' && numCells < 0) {
         numCells = atoi(++*argv);
      }

      if (**argv == 'S' && numSteps < 0) {
         numSteps = atoi(++*argv);
      }

      if (**argv == 'L' && left == 0.0) {
         left = atof(++*argv);
      }
      
      if (**argv == 'R' && right == 0.0) {
         right = atof(++*argv);
      }
   }
   if (numSteps < 0.0 || numCells <= 0 || (numCells == 1 && right != 0)) {
      fprintf(stderr, "Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }

   parentPipe = PipeMe(numCells, numSteps, left, right, pid);

   for (counter = 0; counter < numCells; counter++) {
      cellReports[counter] = numSteps + 1;
   }
   while (read(parentPipe, &cell, sizeof(Report))) {
      printf("Result from %d, step %d: %.3f\n", cell.id, cell.step, 
       cell.value);
      cellReports[cell.id]--;
   }

   for (counter = 0; counter < numCells; counter++) {
      if (cellReports[counter] > 0) {
         fewReports++;
      }
      else if (cellReports[counter] < 0) {
         manyReports++;
      }
   }
   if (fewReports) {
      fprintf(stderr, "Error: %d cells reported too few reports\n", fewReports);
   }
   if (manyReports) {
      fprintf(stderr, "Error: %d cells reported too many reports\n", 
       manyReports);
   }

   for (counter = 0; counter < numCells; counter++) {
      waitpid(pid[counter], &status, 0);
      if (WEXITSTATUS(status) != 0) {
         fprintf(stderr, "Error: Child %d exited with %d\n", counter, 
          WEXITSTATUS(status));
         exited++;
      }
   }
   if (fewReports || manyReports || exited) {
      exit(EXIT_FAILURE);
   }

   exit(EXIT_SUCCESS);
}