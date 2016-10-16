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

//The currently-running process
proc_t *current_proc;

//OLD Process Stacks
//static size_t proc_stacks[NUM_PROCS][DEFAULT_STACK_SIZE];

//Limits for memory allocation
size_t FREE_MEM_BEGIN = 0;
size_t FREE_MEM_END = 0;

//temprary holder for newly exec process's pc
size_t exec_pc = 0;


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

		p->sp = (size_t *)_sbrk(DEFAULT_STACK_SIZE) + (size_t)DEFAULT_STACK_SIZE;

		assert(p->sp != NULL,"sp is null");

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
int fork_proc(proc_t *p1){
	proc_t *original = p1;
	proc_t *p = NULL;
	int priority = 0;

	int i = 0;

	if(p = get_free_proc()) {
		for(i = 0;i<NUM_REGS;i++){
			p->regs[i] = original->regs[i];
		}
		p->priority = original->priority;
		p->pc = original->pc;
		p->ra = original->ra;
		p->rbase = original->rbase;
		p->cctrl = original->cctrl;

		//Initialise protection table
		//TODO: this loop allows unrestricted access to all memory.
		//Update to only enable memory blocks belonging to the process.
		p->ptable = p->protection_table;
		for(i = 0; i < PROTECTION_TABLE_LEN; i++) {
			p->protection_table[i] = 0xffffffff;
		}

		priority = p->priority = original->priority;
		p->quantum = original->quantum;
		p->ticks_left = original->ticks_left;
		p->next = original->next;
		p->sender_q = original->sender_q;
		p->next_sender = original->next_sender;
		p->message = original->message;

		p->time_used = original->time_used;

		strcpy(p->name,"fork_");
 	 	strcat(p->name,original->name);

		//Set the process to runnable, and enqueue it.
		p->state = RUNNABLE;

		p->flags = original->flags;
		process_overview();
		//printf("before at p %d, proc_i %d\r\n",priority,ready_q[priority][HEAD]->proc_index );
		enqueue_tail(ready_q[priority], p);
		//printf("before at p %d, proc_i %d\r\n",priority,ready_q[priority][HEAD]->proc_index );
		process_overview();
	}
	assert(p != NULL, "Fork");

	// printf("original ptable %x\r\n",(void*)&(original->ptable));
	// for(i = 0; i < PROTECTION_TABLE_LEN; i++) {
	// 	printf("0x%x ",(size_t)original->protection_table[i]);
	// }
	// printf("\r\nnew ptable %x\r\n",(void*)&(p->ptable));
	// for(i = 0; i < PROTECTION_TABLE_LEN; i++) {
	// 	printf("0x%x ",(size_t)p->protection_table[i]);
	// }

	// printf("\r\noriginal ");
	// printProceInfo(original);
	// printf("forked");
	// printProceInfo(p);

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

		strcpy(p->name,name);

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
		printf("\r\ncurrent_proc sp 0x%x name %s state %s\r\n", current_proc->sp,current_proc->name,getStateName(current_proc->state));
	}
	for (i=0; i < NUM_QUEUES; i++) {
		if (ready_q[i][HEAD] != NULL) {
			printf("\r\npriority %d\r\n",i );
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
	return 0;
}



int winix_exec(char* lines[],int line_length){
	size_t *base = (size_t*)FREE_MEM_BEGIN;

	return 0;
}


int winix_load_srec_data_length(char *line){
  int i=0;

  int index = 0;
	int checksum = 0;
  byte byteCheckSum = 0;
	int recordType = 0;
	int byteCount = 0;
	char buffer[128];
	char tempBufferCount = 0;

  int wordsCount = 0;
  int length = 0;
  int readChecksum = 0;
  int data = 0;

        index = 0;
        checksum = 0;

				printf("%s\r\n",line);
        //printf("loop %d\n",linecount );
				//Start code, always 'S'
				assert(line[index++] == 'S',"Expecting S");

				recordType = line[index++] - '0';
        if (recordType == 5 || recordType == 6) {

        }else{
          printf("recordType %d\n",recordType );
          printf("format is incorrect\n" );
          return -1;
        }
        tempBufferCount = Substring(buffer,line,index,2);
				//printf("record value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				byteCount = hex2int(buffer,tempBufferCount);
        index += 2;
        checksum += byteCount;

				assert(byteCount<255,"byteCount bigger than 255");

						tempBufferCount = Substring(buffer,line,index,(byteCount-1)*2 );
						//printf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						data = hex2int(buffer,tempBufferCount);
            //printf("data %d\n", data);
            index += (byteCount-1)*2;
            checksum += data;

				//Checksum, two hex digits. Inverted LSB of the sum of values, including byte count, address and all data.
				//readChecksum = (byte)Convert.ToInt32(line.Substring(index, 2), 16);
        //printf("checksum %d\n",checksum );
				tempBufferCount = Substring(buffer,line,index,2);
				//printf("read checksum value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				readChecksum = hex2int(buffer,tempBufferCount);
        // printf("readChecksum %d\n",readChecksum );
        // printf("checksum %d\n",checksum );
        //printf("checksum %d\r\n",checksum );
        if (checksum > 255) {
          byteCheckSum = (byte)(checksum & 0xFF);
          //printf("checksum %d\r\n",byteCheckSum );
          byteCheckSum = ~byteCheckSum;
        }else{
          byteCheckSum = ~byteCheckSum;
          byteCheckSum = checksum;
        }
        //printf("checksum %d\r\n",byteCheckSum );
				if (readChecksum != byteCheckSum){
					printf("failed checksum\r\n" );
					return -1;
				}
        return data;
}


int winix_load_srec_mem_val(char *(*lines), int length,int lines_start_index,int wordsLength){
	char memValues[1];
  int wordsCount = 0;
	int wordsLoaded = 0;
	int index = 0;
	int checksum = 0;
  byte byteCheckSum = 0;
	int recordType = 0;
	int addressLength = 0;
	int byteCount = 0;
	char buffer[128];
	char tempBufferCount = 0;
	int address = 0;
	byte data[255];
	int readChecksum = 0;
	int datalength = 0;
	size_t memVal = 0;
  int i = 0;
  int j = 0;
  int linecount = lines_start_index;

	while(1){

		char* line = lines[linecount];
    linecount++;
    index = 0;
    checksum = 0;

				//printf("%s\r\n",line);
        //printf("loop %d\n",linecount );
				//Start code, always 'S'
				assert(line[index++] == 'S',"Expecting S");

				//Record type, 1 digit, 0-9, defining the data field
				//0: Vendor-specific data
				//1: 16-bit data sequence
				//2: 24 bit data sequence
				//3: 32-bit data sequence
				//5: Count of data sequences in the file. Not required.
				//7: Starting address for the program, 32 bit address
				//8: Starting address for the program, 24 bit address
				//9: Starting address for the program, 16 bit address
				recordType = line[index++] - '0';

				switch (recordType)
				{
						case 0:
						case 1:
						case 9:
								addressLength = 2;
								break;

            case 5:
            case 6:
                addressLength = 0;
                break;

						case 2:
						case 8:
								addressLength = 3;
								break;

						case 3:
						case 7:
								addressLength = 4;
								break;

						default:
								printf("unknown record type");
								return 0;
				}
				tempBufferCount = Substring(buffer,line,index,2);
				//printf("record value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				byteCount = hex2int(buffer,tempBufferCount);
        index += 2;
        checksum += byteCount;

				//byteCount = ((int)line[index++])*10 + ((int)line[index++]);
				//int byteCount = Convert.ToInt32(line.Substring(index, 2), 16);
				//printf("byteCount %d\r\n",byteCount);



				//Address, 4, 6 or 8 hex digits determined by the record type
				for (i = 0; i < addressLength; i++)
				{
						tempBufferCount = Substring(buffer,line,index+i*2,2);
						//printf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						checksum += hex2int(buffer,tempBufferCount);
						//string ch = line.Substring(index + i * 2, 2);
						//checksum += Convert.ToInt32(ch, 16);
				}
        if (addressLength!=0) {
          tempBufferCount = Substring(buffer,line,index,addressLength*2);
  				//printf("temp address value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
  				address = hex2int(buffer,tempBufferCount);
        }


				//address = Convert.ToInt32(line.Substring(index, addressLength * 2), 16);
        //printf("index %d\n",index );
        index += addressLength * 2;
        //printf("index %d\n",index );
				byteCount -= addressLength ;
        //printf("byteCount %d\n",byteCount );
				//Data, a sequence of bytes.
				//data.length = 255
				assert(byteCount<255,"byteCount bigger than 255");
				for (i = 0; i < byteCount-1; i++)
				{
						tempBufferCount = Substring(buffer,line,index,2);
						//printf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						data[i] = hex2int(buffer,tempBufferCount);
						//data[i] = (byte)Convert.ToInt32(line.Substring(index, 2), 16);
						index += 2;
						checksum += data[i];
				}

				//Checksum, two hex digits. Inverted LSB of the sum of values, including byte count, address and all data.
				//readChecksum = (byte)Convert.ToInt32(line.Substring(index, 2), 16);

				tempBufferCount = Substring(buffer,line,index,2);
				//printf("read checksum value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				readChecksum = hex2int(buffer,tempBufferCount);
        //printf("checksum %d\r\n",checksum );
				byteCheckSum = (byte)(checksum & 0xFF);
        //printf("checksum %d\r\n",byteCheckSum );
        byteCheckSum = ~byteCheckSum;
        //printf("checksum %d\r\n",byteCheckSum );
				if (readChecksum != byteCheckSum){
					printf("failed checksum\r\n" );
					return -1;
				}

				//Put in memory
				assert((byteCount-1) % 4 == 0, "Data should only contain full 32-bit words.");
        //printf("recordType %d\n", recordType);
        //printf("%lu\n",(size_t)data[0] );
        //printf("byteCount %d\n",byteCount );
        switch (recordType)
				{
						case 3: //data intended to be stored in memory.

								for (i = 0; i < byteCount-1; i += 4)
								{
										memVal = 0;
										for (j = i; j < i + 4; j++)
										{

												memVal <<= 8;
												memVal |= data[j];
                        	//printf("0x%08x\n",(unsigned int)memVal );
										}
                    memValues[wordsLoaded] = memVal;
										wordsLoaded++;

                    if (wordsLoaded > wordsLength) {
                      printf("words exceed max length\n" );
                      return -1;
                    }
										//printf("0x%08x\n",(unsigned int)memVal );
								}

								break;


						case 7: //entry point for the program.
								// CPU.PC = (uint)address;
								break;
				}
        if (linecount >= length) {
          break;
        }
		}

		return wordsLoaded;
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
	//Initialise queues
	for(i = 0; i < NUM_QUEUES; i++) {
		ready_q[i][HEAD] = NULL;
		ready_q[i][TAIL] = NULL;
	}

	free_proc[HEAD] = free_proc[TAIL] = NULL;
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
