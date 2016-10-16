/**
 * Process Management for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#ifndef _PROC_H_
#define _PROC_H_

//Process & Scheduling
#define PROC_NAME_LEN			20
#define NUM_PROCS				20
#define NUM_QUEUES				5
#define IDLE_PRIORITY			4
#define USER_PRIORITY			3
#define SYSTEM_PRIORITY			0


//Process Defaults
#define DEFAULT_FLAGS			0
#define PROTECTION_TABLE_LEN	32
#define DEFAULT_STACK_SIZE		200
#define DEFAULT_CCTRL			0xff9
#define USER_CCTRL			0x8 //OKU is set to 0
#define DEFAULT_RBASE			0x00000
#define DEFAULT_PTABLE			0x00000
#define DEFAULT_QUANTUM			100
#define DEFAULT_REG_VALUE		0xffffffff
#define DEFAULT_MEM_VALUE		0xffffffff
#define DEFAULT_RETURN_ADDR		0x00000000
#define DEFAULT_PROGRAM_COUNTER	0x00000000

//Process Flags
#define SENDING					0x0001
#define RECEIVING				0x0002

/**
 * State of a process.
 **/
typedef enum { DEAD, INITIALISING, RUNNABLE, ZOMBIE } proc_state_t;

/**
 * Process structure for use in the process table.
 *
 * Note: 	Do not update this structure without also
 * 			updating the definitions in "wramp.s"
 **/
typedef struct proc {
	/* Process State */
	unsigned long regs[NUM_REGS];	//Register values
	unsigned long *sp;
	void *ra;
	void (*pc)();
	void *rbase;
	unsigned long *ptable;
	unsigned long cctrl;

	/* Protection */
	unsigned long protection_table[PROTECTION_TABLE_LEN];

	/* Scheduling */
	int priority;		//Default priority
	int quantum;		//Timeslice length
	int ticks_left;		//Timeslice remaining
	struct proc *next;	//Next pointer

	/* IPC */
	struct proc *sender_q;	//Head of process queue waiting to send to this process
	struct proc *next_sender; //Link to next sender in the queue
	message_t *message;	//Message buffer;

	/* Accounting */
	int time_used;		//CPU time used

	/* Metadata */
	char name[PROC_NAME_LEN];		//Process name
	proc_state_t state;	//Current process state
	int flags;

	/* Process Table Index */
	int proc_index;		//Index in the process table

	unsigned long length;
	unsigned long *malloced_ba;

} proc_t;

//The process table.
extern proc_t proc_table[NUM_PROCS];

/**
 * Initialises the process table and scheduling queues.
 **/
void init_proc();
void proc_set_default(proc_t *p);
/**
 * Creates a new process and adds it to the runnable queue.
 **/
proc_t *new_proc(void (*entry)(), int priority, const char *name);

/**
 * WINIX Scheduler.
 **/
void sched();

/**
 * Frees up a process.
 *
 * Parameters:
 *   p		The process to remove.
 **/
void end_process(proc_t *p);

/**
 * Gets a pointer to a process.
 *
 * Parameters:
 *   proc_nr		The process to retrieve.
 *
 * Returns:			The relevant process, or NULL if it does not exist.
 **/
proc_t *get_proc(int proc_nr);

//void *p_malloc(size_t size);


//fork the next process in the ready_q, return the new proc_index of the forked process
//side effect: the head of the free_proc is dequeued, and added to the ready_q with all relevant values equal
//to the original process, except stack pointer.
int fork_proc(proc_t *p);


int process_overview();
void printProceInfo(proc_t* curr);
char* getStateName(proc_state_t state);

proc_t *new_proc_from_binaryRecords( size_t *lines,size_t length, size_t entry, int priority, char *name);
void load_proc_from_binaryRecords(proc_t *p, size_t *lines,size_t length, size_t entry, int priority, char *name);
void *exec_binary(proc_t *p,size_t *lines,size_t length);
int wipe_proc(proc_t *p);

/**
 * Receives a message.
 *
 * Parameters:
 *   m				Pointer to write the message to.
 *
 * Returns:
 *   0 on success
 *   -1 if destination is invalid
 **/
int wini_send(int dest, message_t *m);

/**
 * Receives a message.
 *
 * Parameters:
 *   m				Pointer to write the message to.
 *
 * Returns:			0
 **/
int wini_receive(message_t *m);

proc_t *exec_proc(size_t *lines, size_t length, size_t entry, int priority, char *name);


/**
 * Pointer to the current process.
 **/
extern proc_t *current_proc;

#endif
