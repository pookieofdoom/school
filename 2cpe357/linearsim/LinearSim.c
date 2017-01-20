#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "Report.h"

#define MAX_CHAR 6
#define MAX_FLOAT_CHARS 18

typedef struct {
   char timeCounter[MAX_CHAR];
   char leftValue[MAX_FLOAT_CHARS];
   char rightValue[MAX_FLOAT_CHARS];
   int numCells, cFlag;
   int lFlag, rFlag, sFlag;
   
}ArgStruct;

typedef struct {
   int parentPipe[2];
   int childPipeLeft[2];
   int childPipeRight[2];
   int prevChildPipeLeft[2];
   int prevChildPipeRight[2];
}PipeStruct;

void InitArgStruct(ArgStruct *args) {
   
   memset(args->timeCounter, '\0', MAX_CHAR);
   memset(args->leftValue, '\0', MAX_FLOAT_CHARS);
   memset(args->rightValue, '\0', MAX_FLOAT_CHARS);
   args->numCells = 0;
   args->cFlag = 0;
   args->lFlag = 0;
   args->rFlag = 0;
   args->sFlag = 0;
}

void ReadCmd(char **argv, ArgStruct *args) {
   while (*++argv) {
      
      if (**argv == 'C' && !args->cFlag) {
         args->numCells = atoi(++*argv);
         args->cFlag = 1;
      }
      else if (**argv == 'S' && !args->sFlag) {
         strcpy(args->timeCounter, *argv);
         args->sFlag = 1;
      }  
      else if (**argv == 'L' && !args->lFlag) {
         strcpy(args->leftValue, ++*argv);

         if (strlen(args->leftValue) > MAX_FLOAT_CHARS) {
            fprintf(stderr, "Left value has too many characters\n");
            exit(EXIT_FAILURE);
         }
         args->lFlag = 1;
      }
      else if (**argv == 'R' && !args->rFlag) {
         strcpy(args->rightValue, ++*argv);

         if (strlen(args->rightValue) > MAX_FLOAT_CHARS) {
            fprintf(stderr, "Right value has too many characters\n");
            exit(EXIT_FAILURE);
         }
         args->rFlag = 1;
      }
   }
   
   if (!args->cFlag || !args->sFlag || 
    (args->numCells == 1 && args->rFlag && args->lFlag)
    || (args->numCells == 1 && args->rFlag)) {
      fprintf(stderr, "Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }
}

void LeftChild(PipeStruct *linearPipe, ArgStruct *args, char *uniqueId) {
   char childWriterRight[MAX_CHAR];
   char fixValue[MAX_FLOAT_CHARS + 2] = "V";
   char parentWriter[MAX_CHAR];
   
   sprintf(parentWriter, "O%d", linearPipe->parentPipe[1]);
   close(linearPipe->childPipeLeft[0]);
   close(linearPipe->childPipeLeft[1]);
   close(linearPipe->childPipeRight[0]);
   
   if (args->numCells == 2) {
      close(linearPipe->childPipeRight[1]);
      childWriterRight[0] = '\0';
   }
   else {
      sprintf(childWriterRight, "O%d", linearPipe->childPipeRight[1]);
   }

   if (args->lFlag) {
      strcat(fixValue, args->leftValue);
   }
   else
      strcat(fixValue, "0");
   printf("this is fixValue %s\n", fixValue);
   printf("HI\n");
   execlp("./Cell", "argZero", args->timeCounter, fixValue,
    parentWriter, childWriterRight, uniqueId, NULL);
}

void RightChild(PipeStruct *linearPipe, ArgStruct *args, char *uniqueId) {
   char childWriterLeft[MAX_CHAR];
   char fixValue[MAX_FLOAT_CHARS + 2] = "V";
   char parentWriter[MAX_CHAR];
   
   sprintf(parentWriter, "O%d", linearPipe->parentPipe[1]);
   close(linearPipe->childPipeLeft[0]);
   close(linearPipe->childPipeLeft[1]);
   close(linearPipe->childPipeRight[0]);
   close(linearPipe->childPipeRight[1]);
   close(linearPipe->prevChildPipeRight[0]);
   close(linearPipe->prevChildPipeRight[1]);
   close(linearPipe->prevChildPipeLeft[0]);

   if (args->numCells == 2) {
      close(linearPipe->prevChildPipeLeft[1]);
      childWriterLeft[0] = '\0';
   } 
   else {
      sprintf(childWriterLeft, "O%d", linearPipe->prevChildPipeLeft[1]);
   }

   if (args->rFlag)
      strcat(fixValue, args->rightValue);
   else
      strcat(fixValue, "0");
   execlp("./Cell", "argZero", args->timeCounter, fixValue,
    parentWriter, childWriterLeft, uniqueId, NULL);
}

void MiddleChild(PipeStruct *linearPipe, ArgStruct *args,
 char *uniqueId, int ndx) {
   char parentWriter[MAX_CHAR];
   char childWriterLeft[MAX_CHAR], childReaderLeft[MAX_CHAR];
   char childWriterRight[MAX_CHAR], childReaderRight[MAX_CHAR];
   
   sprintf(parentWriter, "O%d", linearPipe->parentPipe[1]);
   close(linearPipe->prevChildPipeRight[1]);
   close(linearPipe->prevChildPipeLeft[0]);
   close(linearPipe->childPipeRight[0]);
   close(linearPipe->childPipeLeft[1]);
   
   if (ndx == 1) {
      close(linearPipe->prevChildPipeLeft[1]);
      childWriterLeft[0] = '\0';
   } 
   else {
      sprintf(childWriterLeft, "O%d", linearPipe->prevChildPipeLeft[1]);
   }

   if (ndx == args->numCells - 2) {
      close(linearPipe->childPipeRight[1]);
      childWriterRight[0] = '\0';
   } 
   else {
      sprintf(childWriterRight, "O%d", linearPipe->childPipeRight[1]);
   }

   sprintf(childReaderLeft, "I%d", linearPipe->prevChildPipeRight[0]);
   sprintf(childReaderRight, "I%d", linearPipe->childPipeLeft[0]);
   
   execlp("./Cell", "argZero", args->timeCounter, parentWriter,
    childReaderLeft, childWriterLeft, childWriterRight, 
    childReaderRight, uniqueId, NULL);
}

void Parent(PipeStruct *linearPipe) {
   close(linearPipe->prevChildPipeLeft[0]);
   close(linearPipe->prevChildPipeLeft[1]);
   close(linearPipe->prevChildPipeRight[0]);
   close(linearPipe->prevChildPipeRight[1]);

   linearPipe->prevChildPipeLeft[0] = linearPipe->childPipeLeft[0];
   linearPipe->prevChildPipeLeft[1] = linearPipe->childPipeLeft[1];
   linearPipe->prevChildPipeRight[0] = linearPipe->childPipeRight[0];
   linearPipe->prevChildPipeRight[1] = linearPipe->childPipeRight[1];
}

void CheckReportNumber(ArgStruct *args, int *reportList) {
   int ndx, fewNumSteps = 0, manyNumSteps = 0;
   
   for (ndx = 0; ndx < args->numCells; ndx++) {
      if (reportList[ndx] < atoi(args->timeCounter + 1) + 1)
         fewNumSteps++;

      if (reportList[ndx] > atoi(args->timeCounter + 1) + 1)
         manyNumSteps++;
   }
   if (fewNumSteps) {
      fprintf(stderr,
       "Error: %d cells reported too few reports\n", fewNumSteps);
      exit(EXIT_FAILURE);
   }
   
   if (manyNumSteps) {
      fprintf(stderr,
       "Error: %d cells reported too many reports\n", manyNumSteps);
      exit(EXIT_FAILURE);
   }
   
}

int main(int argc, char **argv) {
   //declarations + initializations
   char uniqueId[MAX_CHAR];
   int ndx, pid = 0;
   int status, exitFlag = 0;
   PipeStruct linearPipe = { {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
   int *pidList; //used for keeping track of pid for error reporting
   int *reportList; //used for keeping track of # of reports
   Report report;
   ArgStruct args;
   
   InitArgStruct(&args);
   pipe(linearPipe.parentPipe);
   ReadCmd(argv, &args);
   pidList = calloc(args.numCells, sizeof(int));
   reportList = calloc(args.numCells, sizeof(int));
   //printf("WHY\n");
   //fork and connect the pipes
   
   for (ndx = 0; ndx < args.numCells; ndx++) {
      sprintf(uniqueId, "D%d", ndx);
      pipe(linearPipe.childPipeLeft);
      pipe(linearPipe.childPipeRight);
      pid = fork();
      
      if (pid < 0) {
        // REMEMBER TO HANDLE FORK ERROR
      } 
      //child 
      else if (pid == 0) {
         close(linearPipe.parentPipe[0]);
        
         //left most cell
         if (ndx == 0) { 
            LeftChild(&linearPipe, &args, uniqueId);
         }
         //right most cell
         else if (ndx == args.numCells - 1) {
            RightChild(&linearPipe, &args, uniqueId);
         }
         //in between cells  
         else {
            MiddleChild(&linearPipe, &args, uniqueId, ndx);
         }
      } 
      //parent
      else if (pid > 0) {
         pidList[ndx] = pid;
         Parent(&linearPipe);
      }      
   }

   if (pid > 0) {
      close(linearPipe.parentPipe[1]);
            
      while (read(linearPipe.parentPipe[0], &report, sizeof(Report))) {
         printf("Result from %d, step %d: %.3f\n",
          report.id, report.step, report.value);
         reportList[report.id]++;
      }
      close(linearPipe.parentPipe[0]);
      
      for (ndx = 0; ndx < args.numCells; ndx++) {
         waitpid(pidList[ndx], &status, 0);
         
         if (status) {
            fprintf(stderr,
             "Error: Child %d exited with %d\n", ndx, WEXITSTATUS(status));
            exitFlag = 1;
         }  
      }
   }
   
   CheckReportNumber(&args, reportList);
   free(pidList);
   free(reportList);
   if (exitFlag)
      exit(EXIT_FAILURE);
   exit(EXIT_SUCCESS);
}
