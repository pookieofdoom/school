#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CCOUNT 3

/* Send our pid on "out" for the next process in the triangle to receive. Run
 * a "bucket brigade", getting a pid from the prior process in the triangle  
 * via "in", and passing it along, so that all processes see each pid once.
 * Total up the pids and send them to the parent via "report". */
void SendTotal(int report, int in, int out, int pid) {
   int i, total = pid;

    for (i = 0; i < 2; i++) {         // Base: 13, Surcharge: 1.2
      write(out, &pid, sizeof(pid)); // Base: 7, Surcharge: 0
      read(in, &pid, sizeof(pid));   // Base: 7, Surcharge: 0
      total += pid;                  // Base: 3, Surcharge: 0
   }               


   write(report, &total, sizeof(total));

   close(out);
   /* Check that there is no lingering data on "in" */
   if (0 != read(in, &pid, sizeof(pid))) 
      printf("Missing EOF on pipe, pid is %d and read is %d\n.", pid, read(in, &pid, sizeof(pid)));

   close(in);
   close(report);
   


}

int main() {
   int i, checkTotal, pidTotal;

   // Pipes to parent, and between three children A, B, C
   int reportFds[2], pAtoB[2], pBtoC[2], pCtoA[2]; 
   
   pipe(reportFds);
   pipe(pCtoA);
   pipe(pAtoB);

   if (!fork()) { /* Child A */
      
      close(pCtoA[1]);
      close(pAtoB[0]);
      close(reportFds[0]);
      printf("sup\n");

      SendTotal(reportFds[1], pCtoA[0], pAtoB[1], getpid());
   }
   else {
      /* Set up for child B */
      /*1*/
     close(pAtoB[1]); 
     pipe(pBtoC);
      printf("howdy\n");

      if (!fork()) { // Do child B
         close(pCtoA[1]);
         close(pBtoC[0]);
         close(reportFds[0]);
         
         SendTotal(reportFds[1], pAtoB[0], pBtoC[1], getpid());
      }
      else {
         /* Set up for child C */
         
         close(pBtoC[1]);
         printf("hi\n");

         if (!fork()) { // Do child C
            close(reportFds[0]);
            SendTotal(reportFds[1], pBtoC[0], pCtoA[1], getpid());
         }
         else {
            
            close(reportFds[1]);
            printf("wat\n");

            close(pBtoC[0]);
            close(pCtoA[1]);

            for (i = pidTotal = 0; i < CCOUNT; i++) {
               pidTotal += wait(NULL);
               printf("Child exits..\n");
            }
            for (i = 0; i < CCOUNT; i++)
               if (0 < read(reportFds[0], &checkTotal, sizeof(checkTotal))
                && checkTotal == pidTotal)
                  printf("Good report\n");

            if (0 == read(reportFds[0], &checkTotal, sizeof(checkTotal)))
               printf("Good EOF\n");

            close(reportFds[0]);
         }
      }
   }

   return 0;
}
