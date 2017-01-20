/**
 * CPE 453 Spring 2012
 * Assignment 02
 * https://users.csc.calpoly.edu/~pnico/class/s12/cpe453/asgn/asgn2/asgn2.pdf
 * 
 * Implementation of a simplistic threading system.
 *
 * Function header comments are stolen directly from the assignment.
 *
 * @author James Pearson
 */

#include "lwp.h"

#include <stdlib.h>
#include <unistd.h>

schedfun gScheduler = NULL;
void * gStackPointer;
unsigned int nextPid = 0;

/* the process table                      */
lwp_context lwp_ptable[LWP_PROC_LIMIT];
/* the current number of LWPs             */
int lwp_procs = 0;
/* the index of the currently running LWP */
int lwp_running;

/**
 * Creates a new lightweight process which calls the given function with the
 * given argument.  The new process's stack will be `stacksize` words.  The
 * LWP's process table entry will include:
 *    `pid`        a unique integer process id
 *    `stack`      a pointer to the memory region for this thread's stack
 *    `stacksize`  the size of this thread's stack in words
 *    `sp`         this thread's current stack pointer (top of stack)
 * @return the lightweight process id of the new thread on success
 *         -1 if more than LWP_PROC_LIMIT threads already exist
 */
int new_lwp(lwpfun function, void * argument, size_t stacksize) {
    size_t stackSizeInBytes = stacksize * sizeof(int);
    unsigned long * stackPointer;
    unsigned long * basePointer;
    
    /* For simplicity's sake, we limit ourselves to a set number of LWPs. */
    if (lwp_procs == LWP_PROC_LIMIT) {
        return -1;
    }
    /* lwp_running is 0-based, so set it *before* incrementing lwp_procs. */
    lwp_running = lwp_procs;
    lwp_procs++;
    
    lwp_ptable[lwp_running].pid = nextPid++;
    lwp_ptable[lwp_running].stack = malloc(stackSizeInBytes);
    lwp_ptable[lwp_running].stacksize = stacksize;
    
    /* Build up our stack in preparation for lwp_yield. */
    /* I am constantly confused about what the stack is supposed to look like.
     * In particular, vertical representations don't help at all, since I view
     * memory as going from left to right.  This is the current assumption:
     *
     * [ s t u f f ]    #######[ space for more stuff ]
     *              |_________| memory available for the stack to use
     *                  ^ stack pointer (top of stack)
     *                         ^ memory available to the process
     */
    stackPointer = lwp_ptable[lwp_running].stack + stackSizeInBytes;
    basePointer = stackPointer;
    *stackPointer = (unsigned long)argument; /* Arg 0 */
    stackPointer--;
    *stackPointer = (unsigned long)lwp_exit;
    stackPointer--;
    *stackPointer = (unsigned long)function; /* Return Address */
    stackPointer--;
    /**stackPointer = (unsigned long)basePointer;*/
    *stackPointer = 0xDEADBEEF;
    basePointer = stackPointer;
    /* Space for the 7 registers SAVE_STATE saves. */
    stackPointer -= 7;
    *stackPointer = (unsigned long)(basePointer);
    
    lwp_ptable[lwp_running].sp = stackPointer;
    
    return lwp_running;
}

/**
 * @return the pid of the calling LWP.  Undefined if not called by a LWP.
 */
int lwp_getpid() {
    return lwp_ptable[lwp_running].pid;
}

/**
 * Yields control to another LWP.  Which one depends on the scheduler.  Saves
 * the current LWP's context, picks the next one, restores that thread's
 * context, and returns.
 */
void lwp_yield() {
    /* Save context for later. */
    SAVE_STATE();
    
    /* Save stack pointer for later. */
    GetSP(lwp_ptable[lwp_running].sp);
    
    /* Pick a thread to run. */
    if (gScheduler == NULL) {
        /* Round-robin. */
        lwp_running++;
        /* Go back to the start of the list if we've reached the end. */
        if (lwp_running == lwp_procs) {
            lwp_running = 0;
        }
    } else {
        lwp_running = gScheduler();
    }
    SetSP(lwp_ptable[lwp_running].sp);
    
    /* And run it. */
    RESTORE_STATE();
}

/**
 * Terminates the current LWP, frees its resources, and moves all the others up
 * in the process table.  If there are no other threads, calls `lwp_stop()`.
 */
void lwp_exit() {
    int i;
    
    /* Return thread's stack to system. */
    free(lwp_ptable[lwp_running].stack);
    
    /* Shift the process table. */
    for (i=lwp_running+1; i<lwp_procs; i++) {
        lwp_ptable[i-1] = lwp_ptable[i];
    }
    
    /* Stop if we don't have any more threads. */
    lwp_procs--;
    if (lwp_procs == 0) {
        lwp_stop();
    } else {
        /* Pick a thread to run. */
        if (gScheduler == NULL) {
            /* Round-robin. */
            /* Let's start at the very beginning, a very good place to start. */
            lwp_running = 0;
        } else {
            lwp_running = gScheduler();
        }
        SetSP(lwp_ptable[lwp_running].sp);
        
        /* And run it. */
        RESTORE_STATE();
    }
}

/**
 * Starts the LWP system.  Saves the original context and stack pointer (for
 * `lwp_stop()` to use later), picks a LWP and start it running.  If there are
 * no LWPs, returns immediately.
 */
void lwp_start() {
    if (lwp_procs == 0) {
        return;
    }
    
    /* Save context for later. */
    SAVE_STATE();
    
    /* Save stack pointer for later. */
    GetSP(gStackPointer);
    
    /* Pick a thread to run. */
    if (gScheduler == NULL) {
        /* Round-robin. */
        /* Let's start at the very beginning, a very good place to start. */
        lwp_running = 0;
    } else {
        lwp_running = gScheduler();
    }
    SetSP(lwp_ptable[lwp_running].sp);
    
    /* And run it. */
    RESTORE_STATE();
}

/**
 * Stops the LWP system, restores the original stack pointer and returns to
 * that context (wherever `lwp_start()` was called from).  Does not destory any
 * existing contexts, and thread processing will be restarted by a call to
 * `lwp_start()`.
 */
void lwp_stop() {
    /* Save context for later. */
    SAVE_STATE();
    
    /* Reset stack pointer to original context. */
    SetSP(gStackPointer);
    
    /* Continue on our way. */
    RESTORE_STATE();
}

/**
 * Causes the LWP package to use the function `scheduler` to choose the next
 * process to run.  `(*scheduler)()` must return an integer in the range
 * 0...lwp_procs - 1, representing an index into `lwp_ptable`, or -1 if there
 * is no thread to schedule.
 * If `scheduler` is null or has never been set, the scheduler should do
 * round-robin scheduling.
 */
void lwp_set_scheduler(schedfun scheduler) {
    gScheduler = scheduler;
}