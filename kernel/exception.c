/**
 * Exception-handling routines for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include "winix.h"
#include <sys/syscall.h>

//Number of exception sources
#define NUM_HANDLERS 16

//Handler prototypes
static void button_handler();
static void timer_handler();
static void parallel_handler();
static void serial1_handler();
static void serial2_handler();
static void gpf_handler();
static void syscall_handler();
static void break_handler();
static void arith_handler();
static void no_handler();

//Table of all handlers.
//Position in the table corresponds to relevant bit of $estat
static void (*handlers[])(void) = {
	no_handler, 		//Undefined
	no_handler, 		//Undefined
	no_handler, 		//Undefined
	no_handler, 		//Undefined
	no_handler, 		//IRQ0
	button_handler, 	//IRQ1
	timer_handler, 		//IRQ2
	parallel_handler, 	//IRQ3
	serial1_handler, 	//IRQ4
	serial2_handler, 	//IRQ5
	no_handler, 		//IRQ6
	no_handler, 		//IRQ7
	gpf_handler, 		//GPF
	syscall_handler, 	//SYSCALL
	break_handler, 		//BREAK
	arith_handler 		//ARITH
};

//System uptime, stored as number of timer interrupts since boot
int system_uptime = 0;

/**
 * User Interrupt Button (IRQ1)
 **/
static void button_handler() {
	RexUserInt->Iack = 0;
}

/**
 * Timer (IRQ2)
 *
 * Side Effects:
 *   system_uptime is incremented
 *   scheduler is called (i.e. this handler does not return)
 **/
static void timer_handler() {
	RexTimer->Iack = 0;
	
	//Increment uptime and call scheduler
	system_uptime++;
	sched();
}

/**
 * Parallel Port (IRQ3)
 **/
static void parallel_handler() {
	RexParallel->Iack = 0;
}

/**
 * Serial Port 1 (IRQ4)
 **/
static void serial1_handler() {
	RexSp1->Iack = 0;
}

/**
 * Serial Port 2 (IRQ5)
 **/
static void serial2_handler() {
	RexSp2->Iack = 0;
}

/**
 * General Protection Fault.
 *
 * Side Effects:
 *   Current process is killed.
 *   Scheduler is called (i.e. this handler does not return).
 **/
static void gpf_handler() {
	//Current process has performed an illegal operation and will be shut down.
	printf("\r\n[SYSTEM] Process \"%s (%d)\" GPF: PC=%x.\r\n",
		current_proc->name,
		current_proc->proc_index,
		current_proc->pc);
	
	//Kill process and call scheduler.
	end_process(current_proc);
	current_proc = NULL;
	sched();
}

/**
 * System Call.
 *
 **/
static void syscall_handler() {
	int src, dest, operation;
	message_t *m;
	int *retval;
	proc_t *p;	
	
	//TODO: the following does not account for virtual memory offsets.
	operation = *current_proc->sp;				//Operation is the first parameter on the stack
	dest = *(current_proc->sp + 1);				//Destination is second parameter on the stack
	m = *(message_t **)(current_proc->sp + 2);	//Message pointer is the third parameter on the stack
	m->src = current_proc->proc_index;			//Don't trust the caller to specify their own source process number
	retval = (int*)&current_proc->regs[0];		//Result is returned in register $1
	
	//Default return value is an error code
	*retval = -1;
	
	//Decode operation
	switch(operation) {
		case WINIX_SENDREC:
			current_proc->flags |= RECEIVING;
			//fall through to send
			
		case WINIX_SEND:
			*retval = wini_send(dest, m);
			break;
			
		case WINIX_RECEIVE:
			*retval = wini_receive(m);
			break;
			
		default:
			break;
	}
	
	//A system call could potentially make a high-priority process runnable.
	//Run scheduler.
	sched();
}

/**
 * Breakpoint.
 **/
static void break_handler() {
	//TODO: implement handling of breakpoints
}

/**
 * Arithmetic Exception.
 *
 * Side Effects:
 *   Current process is killed, and scheduler is called (i.e. this handler does not return).
 **/
static void arith_handler() {
	printf("\r\n[SYSTEM] Process \"%s (%d)\" ARITH: PC=%x.\r\n", current_proc->name, current_proc->proc_index, current_proc->pc);
	end_process(current_proc);
	current_proc = NULL;
	sched();
}

/**
 * Generic handler, should never be called.
 *
 * Side Effects:
 *   System Panic! Does not return.
 **/
static void no_handler() {
	panic("Unhandled Exception");
}

/**
 * The global exception handler.
 * All relevant exception handlers will be called.
 **/
static void exception_handler(int estat) {
	int i;
	
	//Loop through $estat and call all relevant handlers.
	for(i = NUM_HANDLERS; i; i--) {
		if(estat & (1 << i)) {
			handlers[i]();
		}
	}
}

/**
 * Initialises interrupts and exceptions.
 *
 * Side Effects:
 *   System exception handler is initialised.
 *   Timer is configured to generate regular interrupts.
 **/
void init_exceptions() {
	wramp_set_handler(exception_handler);
	
	RexTimer->Load = 40; //60 Hz
	RexTimer->Ctrl = 3; //Enabled, auto-restart
}
