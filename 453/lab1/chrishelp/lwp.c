/* Chris Casil
   CPE 453
   Program 2
*/

#include <stdio.h>
#include <stdlib.h>
#include "lwp.h"

ptr_int_t *stack;
lwp_context lwp_ptable[LWP_PROC_LIMIT];
int PID = 1;
int lwp_procs = 0;
int lwp_running;

int RoundRobin() {
   return (!lwp_procs ? 0 : (lwp_running + 1) % lwp_procs);
}

schedfun whichSched = RoundRobin;

int new_lwp(lwpfun fp, void *args, size_t stacksize) {
   if (lwp_procs > LWP_PROC_LIMIT) {
      return -1;
   }

   ptr_int_t *newStack = calloc(stacksize, sizeof(ptr_int_t));

   lwp_ptable[lwp_procs].pid = PID;
   lwp_ptable[lwp_procs].stack = newStack;
   lwp_ptable[lwp_procs].stacksize = stacksize;

   newStack += stacksize - 1;   
   *newStack-- = (ptr_int_t) args;
   *newStack-- = (ptr_int_t) lwp_exit;
   *newStack-- = (ptr_int_t) fp;
   
   ptr_int_t *ret = newStack; 
   
   newStack -= 8 * sizeof(ptr_int_t);
   *newStack = (ptr_int_t) ret;

   lwp_ptable[lwp_procs++].sp = newStack;

   return PID++;
}

void lwp_exit() {
   if (!(--lwp_procs)) {
      lwp_stop();
      return;
   }
   while (lwp_running < lwp_procs) {
      lwp_ptable[lwp_running] = lwp_ptable[lwp_running + 1];
      lwp_running++;
   }
   lwp_running = whichSched();
   SetSP(lwp_ptable[lwp_running].sp);
   
   RESTORE_STATE();
}

int lwp_getpid() {
   return lwp_ptable[lwp_running].pid;
}

void lwp_yield() {
   SAVE_STATE();
   GetSP(lwp_ptable[lwp_running].sp);
   lwp_running = whichSched();
   SetSP(lwp_ptable[lwp_running].sp);
   RESTORE_STATE();
}

void lwp_start() {
   SAVE_STATE();
   GetSP(stack);
   lwp_running = whichSched();
   SetSP(lwp_ptable[lwp_running].sp);
   RESTORE_STATE();
}

void lwp_stop() {
   if (lwp_procs) {
      SAVE_STATE();
      GetSP(lwp_ptable[lwp_running].sp);
      lwp_running = whichSched();
   }
   SetSP(stack);
   RESTORE_STATE();
}

void lwp_set_scheduler(schedfun sched) {
   whichSched = sched ? sched : RoundRobin;
}