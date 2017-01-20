/*
Anthony Dinh
CPE 453 Lab1 LWP
4/5/2016
*/

#include "lwp.h"
#include <stdlib.h>
#include <stdio.h>

/*function prototype*/
int round_robin();
void set_sp(ptr_int_t **sp, lwpfun func, void *arguments);

/*global variables*/
lwp_context lwp_ptable[LWP_PROC_LIMIT]; /* the process table */
int lwp_procs = 0;           /* the current number of LWPs  */
int lwp_running = -1;         /* the index of the currently running LWP */
ptr_int_t *global_sp;
schedfun global_sched = round_robin;


int  new_lwp(lwpfun func, void *arguments, size_t stacksize) {
   /*stacksize is in words -reminder*/
   if (lwp_procs == LWP_PROC_LIMIT)
      return -1;
  
   /*set struct variables*/
   lwp_running = lwp_procs++;

   lwp_ptable[lwp_running].pid = lwp_running; /* any unique pid value */
   lwp_ptable[lwp_running].stack = malloc(stacksize * sizeof(ptr_int_t));
   lwp_ptable[lwp_running].stacksize = stacksize;

   lwp_ptable[lwp_running].sp = lwp_ptable[lwp_running].stack +(stacksize *sizeof(ptr_int_t));
   /*set up the stack */
   set_sp(&lwp_ptable[lwp_running].sp, func, arguments);
   
   /*returns the lwpid*/
   return lwp_running;
}


void lwp_exit() {
   int shift_index;
   free(lwp_ptable[lwp_running].stack); /*free the stack / resources*/
   
   for (shift_index = lwp_running; shift_index < lwp_procs; shift_index++)
      lwp_ptable[shift_index] = lwp_ptable[shift_index + 1];
   
   if (--lwp_procs) { /*still have threads left*/
      if (global_sched != round_robin)
         lwp_running = global_sched();
      else
         lwp_running = 0; 
      SetSP(lwp_ptable[lwp_running].sp);
      RESTORE_STATE();
   }
   else /*no other threads left*/
      lwp_stop();
}

/*returns the pid of calling LWP*/
int  lwp_getpid() {
   return lwp_ptable[lwp_running].pid;
}

/* pseduo from class for yield
   save_state
   move sp
   pick next process
   restore state */

void lwp_yield() {
   SAVE_STATE(); /*pushes everything onto stack except sp*/
   GetSP(lwp_ptable[lwp_running].sp); /*set the sp to current sp*/
   lwp_running = global_sched(); /*get the next running thread using sched*/
   SetSP(lwp_ptable[lwp_running].sp); /*set sp to the thread's sp*/
   RESTORE_STATE();
}

void lwp_start() {
   SAVE_STATE(); /*save_state*/
   GetSP(global_sp);    /*save sp so lwp_stop can find*/
   lwp_running = global_sched();
   SetSP(lwp_ptable[lwp_running].sp);  /* and switch to its stack*/
   RESTORE_STATE();  /*load context with resotre_state*/
}

void lwp_stop() {
   if (lwp_procs) {
      /* just incase multiple stop and starts.. start should resume in the
        *same thread that stop was called so running */
      SAVE_STATE();
      GetSP(lwp_ptable[lwp_running].sp);
      lwp_running--;
   }
   SetSP(global_sp);
   RESTORE_STATE();
}
   

void lwp_set_scheduler(schedfun sched) {
   if (sched == NULL)
      global_sched = round_robin;
   else
      global_sched = sched;
}

/*schedfun is a function pointer to the schedular function*/
int round_robin(void) {
   //FCFS (FIFO Queue implementation)
   return (lwp_running + 1) % lwp_procs;

}

/* order of stack
   args
   return address
   func
   bp (arbitary value)
   6 general purpose cpu registers
   &bp
*/

void set_sp(ptr_int_t **sp, lwpfun func, void *arguments) {
   ptr_int_t *base_pointer;
   /* (*(*sp)--) is the same as **sp = variable, then (*sp)--*/
   *(*sp)-- = (ptr_int_t)arguments; /*set args, then move pointer*/
   *(*sp)-- = (ptr_int_t)lwp_exit; /*set return address, then move pointer*/
   *(*sp)-- = (ptr_int_t)func; /*function pointer*/
   
   base_pointer = *sp;  /*value in base pointer can be arbitary value*/
   *sp -= 7 ; /*space for the registers*/
   **sp = (ptr_int_t)base_pointer; /*set base pointer address*/
}