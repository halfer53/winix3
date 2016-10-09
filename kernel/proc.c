/**
 * Process scheduling routines for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include "winix.h"

//Linked lists are defined by a head and tail pointer.
#define HEAD 0
#define TAIL 1

//Process table
proc_t proc_table[NUM_PROCS];

//Scheduling queues
static proc_t *ready_q[NUM_QUEUES][2];

//Entries in the process table that are not in use
static proc_t *free_proc[2];

//Entries to the list of unallocated memory space in RAM
static hole_t *holes[2];

//The currently-running process
proc_t *current_proc;

//Process Stacks
//TODO: dynamically allocate stacks during exec system call.
//static unsigned long proc_stacks[NUM_PROCS][DEFAULT_STACK_SIZE];

//Limits for memory allocation
unsigned long FREE_MEM_BEGIN = 0;
unsigned long FREE_MEM_END = 0;

/**
 * Adds a proc to the tail of a list.
 *
 * Parameters:
 *   q		An array containing a head and tail pointer of a linked list.
 *   proc	The proc struct to add to the list.
 **/
static void enqueue_tail(proc_t **q, proc_t *proc) {
	if(q[HEAD] == NULL) {
		q[HEAD] = q[TAIL] = proc;
	}
	else {
		q[TAIL]->next = proc;
		q[TAIL] = proc;
	}
	proc->next = NULL;
}

/**
 * Adds a proc to the head of a list.
 *
 * Parameters:
 *   q		An array containing a head and tail pointer of a linked list.
 *   proc	The proc struct to add to the list.
 **/
static void enqueue_head(proc_t **q, proc_t *proc) {
	if(q[HEAD] == NULL) {
		proc->next = NULL;
		q[HEAD] = q[TAIL] = proc;
	}
	else {
		proc->next = q[HEAD];
		q[HEAD] = proc;
	}
}

/**
 * Removes the head of a list.
 *
 * Parameters:
 *   q		An array containing a head and tail pointer of a linked list.
 *
 * Returns:
 *   The proc struct that was removed from the head of the list
 *   NULL if the list is empty.
 **/
static proc_t *dequeue(proc_t **q) {
	proc_t *p = q[HEAD];

	if(p == NULL) { //Empty list
		assert(q[TAIL] == NULL, "deq: tail not null");
		return NULL;
	}

	if(q[HEAD] == q[TAIL]) { //Last item
		q[HEAD] = q[TAIL] = NULL;
	}
	else { //At least one remaining item
		q[HEAD] = p->next;
	}
	p->next = NULL;
	return p;
}

/**
 * Gets a proc struct that isn't currently in use.
 *
 * Returns:
 *   A pointer to a proc struct that isn't in use.
 *   NULL if there are no free slots in the process table.
 *
 * Side Effects:
 *   A proc struct is removed from the free_proc list, and reinitialised.
 **/
static proc_t *get_free_proc() {
	int i;
	proc_t *p = dequeue(free_proc);
	size_t *sp = NULL;

	if(p) {
		//Clear register values
		for(i = 0; i < NUM_REGS; i++) {
			p->regs[i] = DEFAULT_REG_VALUE;
		}

		//Clear stack
		// for(i = 0; i < DEFAULT_STACK_SIZE; i++) {
		// 	proc_stacks[p->proc_index][i] = DEFAULT_MEM_VALUE;
		// }
		//
		// //Initialise state
		// p->sp = proc_stacks[p->proc_index];


		p->sp = (size_t *)p_malloc(DEFAULT_STACK_SIZE) + (size_t)DEFAULT_STACK_SIZE;
		assert(p->sp != NULL,"sp is null");

		p->sp += DEFAULT_STACK_SIZE; //start at the "top" of the stack
		p->ra = DEFAULT_RETURN_ADDR;
		p->pc = DEFAULT_PROGRAM_COUNTER;
		p->rbase = DEFAULT_RBASE;
		p->ptable = DEFAULT_PTABLE;
		p->cctrl = DEFAULT_CCTRL;

		p->priority = 0;
		p->quantum = DEFAULT_QUANTUM;
		p->ticks_left = 0;
		p->time_used = 0;
		p->state = INITIALISING;
		p->flags = DEFAULT_FLAGS;

		p->sender_q = NULL;
		p->next_sender = NULL;
		p->message = NULL;
	}
	return p;
}

/**
 * Chooses a process to run.
 *
 * Returns:
 *   The process that is runnable with the highest priority.
 *   NULL if no processes are runnable (should never happen).
 *
 * Side Effects:
 *   A proc is removed from a ready_q.
 **/
static proc_t *pick_proc() {
	int i;

	//Find the highest-priority non-empty queue
	for(i = 0; i < NUM_QUEUES; i++) {
		if(ready_q[i][HEAD] != NULL) {
			return dequeue(ready_q[i]);
		}
	}

	return NULL;
}


void Scan_FREE_MEM_BEGIN(){
	FREE_MEM_BEGIN = (unsigned long)&BSS_END;

	//Round up to the next 1k boundary
	FREE_MEM_BEGIN |= 0x03ff;
	FREE_MEM_BEGIN++;

	//Search for upper limit
	//Note: this doubles as a memory test.
	// for(FREE_MEM_END = FREE_MEM_BEGIN; ; FREE_MEM_END++) {
	// 	*(unsigned long*)FREE_MEM_END = FREE_MEM_END; //Write address to memory location
	// 	if(*(unsigned long*)FREE_MEM_END != FREE_MEM_END) { //Check that the value was remembered
	// 		break;
	// 	}
	//
	// 	if(!(FREE_MEM_END & 0x1fff)) { //print '.' every 8k
	// 		putc('.');
	// 	}
	// }
	//
	// //Wind back to the highest 1k block
	// FREE_MEM_END &= (unsigned long)~0x3ff;
	// FREE_MEM_END--;
	printf("\r\nfree memory begin 0x%x\r\n",FREE_MEM_BEGIN );
}




void *p_malloc(size_t size){
	size_t temp = FREE_MEM_BEGIN;
	if (FREE_MEM_END != 0) {
		//if FREE_MEM_END is not null, then that means the OS is running
		//otherwise it's initialising, thus FREE_MEM_END is not set yet
		//we just assume there is enough memory during the start up
		//since calculating FREE_MEM_END during the start up is gonna crash the system for some unknown reason
		if (size + FREE_MEM_BEGIN > FREE_MEM_END) {
			return NULL;
		}
	}

	FREE_MEM_BEGIN += size;
	return (void *)temp;
}


int fork_current_proc(){
	proc_t *original = NULL;
	proc_t *p = NULL;
	char* original_name;
	int i = 0;
	char buffer[PROC_NAME_LEN];

	for(i = 0; i < NUM_QUEUES; i++) {
		if(ready_q[i][HEAD] != NULL) {
			original = ready_q[i][HEAD];
		}
	}

	original_name = original->name;
		buffer[0] = 'f';
		buffer[1] = 'o';
		buffer[2] = 'r';
		buffer[3] = 'k';
		buffer[4] = '_';
		//TODO: replace with strncpy
		for(i = 5; i < PROC_NAME_LEN; i++) {
			buffer[i] = *original_name;

			if(*original_name++ == '\0') {
				break;
			}
	}

	p = new_proc(original->pc, original->priority, buffer);
	assert(p != NULL, "Fork");
	p->ra = original->ra;
	p->pc = original->pc;
	p->cctrl = original->cctrl;
	printf("original\r\n");
	printProceInfo(original);
	printf("forked\r\n");
	printProceInfo(p);


	//error
	//original = &proc_table[2]; would cause error, but [0] wouldn't
	//original = &proc_table[4]; //fork shell.c
	// original_name = original->name;
	// if (p = get_free_proc()) {
	// 	//sp is set to the new process
	// 	p->ra = original->ra;
	// 	p->pc = original->pc;
	// 	p->cctrl = original->cctrl;
	// 	//TODO
	// 	//set up rbase and ptable instead of copying off the original one
	// 	p->rbase = original->rbase;
	//
	// 	//p->ptable = original->ptable;
	//
	// 	//Initialise protection table
	// 	//TODO: this loop allows unrestricted access to all memory.
	// 	//Update to only enable memory blocks belonging to the process.
	// 	p->ptable = p->protection_table;
	// 	for(i = 0; i < PROTECTION_TABLE_LEN; i++) {
	// 		p->protection_table[i] = 0xffffffff;
	// 	}
	//
	// 	p->name[0] = 'f';
	// 	p->name[1] = 'o';
	// 	p->name[2] = 'r';
	// 	p->name[3] = 'k';
	// 	p->name[4] = '_';
	// 	//TODO: replace with strncpy
	// 	for(i = 5; i < PROC_NAME_LEN; i++) {
	// 		p->name[i] = *original_name;
	//
	// 		if(*original_name++ == '\0') {
	// 			break;
	// 		}
	// 	}
	//
	// 	p->priority = original->priority;
	// 	p->quantum = original->quantum;
	// 	//ticks_left and time_used is set to default
	// 	p->state = RUNNABLE;
	// 	//flags, sender_q, next_sender, and message is set to default
	// 	enqueue_tail(ready_q[p->priority],p);
	// }
	return p->proc_index;
}

/**
 * Creates a new process and adds it to the runnable queue
 *
 * Parameters:
 *   entry		A pointer to the entry point of the new process.
 *   priority	The scheduling priority of the new process.
 *   name		The name of the process, up to PROC_NAME_LEN characters long.
 *
 * Returns:
 *   The newly-created proc struct.
 *   NULL if the priority is not valid.
 *   NULL if the process table is full.
 *
 * Side Effects:
 *   A proc is removed from the free_proc list, reinitialised, and added to ready_q.
 */
proc_t *new_proc(void (*entry)(), int priority, const char *name) {
	proc_t *p = NULL;
	int i;

	//Is the priority valid?
	if(!(0 <= priority && priority < NUM_QUEUES)) {
		return NULL;
	}

	//Get a free slot in the process table
	if(p = get_free_proc()) {
		p->priority = priority;
		p->pc = entry;

		//TODO: replace with strncpy
		for(i = 0; i < PROC_NAME_LEN; i++) {
			p->name[i] = *name;

			if(*name++ == '\0') {
				break;
			}
		}

		//Initialise protection table
		//TODO: this loop allows unrestricted access to all memory.
		//Update to only enable memory blocks belonging to the process.
		p->ptable = p->protection_table;
		for(i = 0; i < PROTECTION_TABLE_LEN; i++) {
			p->protection_table[i] = 0xffffffff;
		}

		//Set the process to runnable, and enqueue it.
		p->state = RUNNABLE;
		enqueue_tail(ready_q[priority], p);
	}
	return p;
}

/**
 * Exits a process, and frees its slot in the process table.
 *
 * Note:
 *   The process must not currently belong to any linked list.
 *
 * Side Effects:
 *   Process state is set to DEAD, and is returned to the free_proc list.
 **/
void end_process(proc_t *p) {

	 p->state = DEAD;
	 enqueue_tail(free_proc, p);
}

//print out the list of processes currently in the ready_q
//and the currently running process
//return 0;

int process_overview(){
	int i=0;
	proc_t *curr = NULL;
	if (current_proc != NULL) {
		printf("current_proc sp 0x%x name %s state %s\r\n", current_proc->sp,current_proc->name,getStateName(current_proc->state));
	}
	for (i=0; i < NUM_QUEUES; i++) {
		if (ready_q[i][HEAD] != NULL) {
			printf("priority %d\r\n",i );
			curr = ready_q[i][HEAD];
			while(curr != NULL){
				printProceInfo(curr);
				curr = curr->next;
			}
		}
	}
	return 0;
}

//print the process state given
void printProceInfo(proc_t* curr){
	printf("name %s, proc_index %d, Stack_Address 0x%x, state %s\r\n",curr->name, curr->proc_index, curr->sp,getStateName(curr->state));
}

//return the strign value of state name give proc_state_t state
char* getStateName(proc_state_t state){
	switch (state) {
		case DEAD: return "DEAD";
		case INITIALISING: return "INITIALISING";
		case RUNNABLE: return "RUNNABLE";
		case ZOMBIE: return "ZOMBIE";
		default: return "none";
	}
}


/**
 * The Scheduler.
 *
 * Notes:
 *   Context of current_proc must already be saved.
 *   If successful, this function does not return.
 *
 * Side Effects:
 *   current_proc has its accounting fields updated, and is reinserted to ready_q.
 *   current_proc is updated to point to the next runnable process.
 *   Context of the new proc is loaded.
 **/
void sched() {
	if(current_proc != NULL && !current_proc->flags) {
		//Accounting
		current_proc->time_used++;

		//If there's still time left, reduce timeslice and add it to the head of its priority queue
		if(--current_proc->ticks_left) {
			enqueue_head(ready_q[current_proc->priority], current_proc);
		}
		else { //Re-insert process at the tail of its priority queue
			enqueue_tail(ready_q[current_proc->priority], current_proc);
		}
	}

	//Get the next task
	current_proc = pick_proc();
	assert(current_proc != NULL, "sched: current_proc null");

	//Reset quantum if needed
	if(current_proc->ticks_left == 0) {
		current_proc->ticks_left = current_proc->quantum;
	}

	//Load context and run
	wramp_load_context();
}

/**
 * Gets a pointer to a process.
 *
 * Parameters:
 *   proc_nr		The process to retrieve.
 *
 * Returns:			The relevant process, or NULL if it does not exist.
 **/
proc_t *get_proc(int proc_nr) {
	if(0 <= proc_nr && proc_nr < NUM_PROCS) {
		proc_t *p = &proc_table[proc_nr];
		if(p->state != DEAD)
			return p;
	}
	return NULL;
}

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
int wini_send(int dest, message_t *m) {
	proc_t *pDest;

	current_proc->message = m; //save for later

	//Is the destination valid?
	if(pDest = get_proc(dest)) {

		//If destination is waiting, deliver message immediately.
		if(pDest->flags & RECEIVING) {
			//Copy message to destination
			*(pDest->message) = *m;

			//Unblock receiver
			pDest->flags &= ~RECEIVING;
			enqueue_head(ready_q[pDest->priority], pDest);
		}
		else {
			//Otherwise, block current process and add it to head of sending queue of the destination.
			current_proc->flags |= SENDING;
			current_proc->next_sender = pDest->sender_q;
			pDest->sender_q = current_proc;
		}
		return 0;
	}

	return -1;
}

/**
 * Receives a message.
 *
 * Parameters:
 *   m				Pointer to write the message to.
 *
 * Returns:			0
 **/
int wini_receive(message_t *m) {
	proc_t *p = current_proc->sender_q;

	//If a process is waiting to send to this process, deliver it immediately.
	if(p != NULL) {
		//Dequeue head node
		current_proc->sender_q = p->next_sender;

		//Copy message to this process
		*m = *(p->message);

		//Unblock sender
		p->flags &= ~SENDING;
		enqueue_head(ready_q[p->priority], p);
	}
	else {
		current_proc->message = m;
		current_proc->flags |= RECEIVING;
	}
}

/**
 * Initialises the process table
 *
 * Side Effects:
 *   ready_q is initialised to all empty queues.
 *   free_proc queue is initialised and filled with processes.
 *   proc_table is initialised to all DEAD processes.
 *   current_proc is set to NULL.
 **/
void init_proc() {
	int i;
	printf("0 \r\n" );
	//Initialise queues
	for(i = 0; i < NUM_QUEUES; i++) {
		ready_q[i][HEAD] = NULL;
		ready_q[i][TAIL] = NULL;
	}

	free_proc[HEAD] = free_proc[TAIL] = NULL;
	printf("1 \r\n" );
	//Add all proc structs to the free list
	for(i = 0; i < NUM_PROCS; i++) {
		proc_t *p = &proc_table[i];

		p->state = DEAD;

		enqueue_tail(free_proc, p);
		proc_table[i].proc_index = i;
	}

	//No current process yet.
	current_proc = NULL;
}
