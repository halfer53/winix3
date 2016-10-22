/**
 * System task for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include "winix.h"
#include <stdio.h>
#include <sys/syscall.h>


/**
 * Scans the free memory and sets the globals FREE_MEM_BEGIN and FREE_MEM_END.
 *
 * Note: both of these values must fall on a 1k boundary for memory protection purposes.
 *
 * Side Effects:
 *   FREE_MEM_BEGIN and FREE_MEM_END are initialised.
 *   Characters are printed using putc.
 **/
static void scan_memory() {
	// FREE_MEM_BEGIN = (unsigned long)&BSS_END;
	//
	// //Round up to the next 1k boundary
	// FREE_MEM_BEGIN |= 0x03ff;
	// FREE_MEM_BEGIN++;

	//Search for upper limit
	//Note: this doubles as a memory test.
	for(FREE_MEM_END = FREE_MEM_BEGIN; ; FREE_MEM_END++) {
		*(unsigned long*)FREE_MEM_END = FREE_MEM_END; //Write address to memory location
		if(*(unsigned long*)FREE_MEM_END != FREE_MEM_END) { //Check that the value was remembered
			break;
		}

		if(!(FREE_MEM_END & 0x1fff)) { //print '.' every 8k
			kputc('.');
		}
	}

	//Wind back to the highest 1k block
	FREE_MEM_END &= (unsigned long)~0x3ff;
	FREE_MEM_END--;
}

/**
 * Entry point for system task.
 **/
void system_main() {
	proc_t *curr = ready_q[3][0];
	proc_t *currpro = current_proc;
	int counter = 0;
	//Find Upper Memory Limit
	kprintf("Scanning Memory");
	scan_memory();
	kprintf(" %d kWords Free\r\n", ((unsigned long)(FREE_MEM_END - FREE_MEM_BEGIN)) / 1024);

	//Print Memory Map
	kprintf("Text Segment: 0x%x - 0x%x\r\n", &TEXT_BEGIN, &TEXT_END);
	kprintf("Data Segment: 0x%x - 0x%x\r\n", &DATA_BEGIN, &DATA_END);
	kprintf("BSS Segment:  0x%x - 0x%x\r\n", &BSS_BEGIN, &BSS_END);
	kprintf("Unallocated:  0x%x - 0x%x\r\n", FREE_MEM_BEGIN, FREE_MEM_END);



	//Receive message, do work, repeat.
	while(1) {

		message_t m;
		int who;
		proc_t *p;
		size_t *sptr;
		int response = 0;
		void *ptr = NULL;

		//Get a message
		winix_receive(&m);
		who = m.src;
		p = &proc_table[who];
		//kprintf("received from %s, call id %d, operation %d\n",p->name,p->proc_index,m.type );
		//Do the work
		switch(m.type) {

			//Gets the system uptime.
			case SYSCALL_GETC:
				response = kgetc();
				m.i1 = response;
				winix_send(who,&m);
				break;

			case SYSCALL_UPTIME:
				m.i1 = system_uptime;
				winix_send(who, &m);
				break;

			//Exits the current process.
			case SYSCALL_EXIT:
				kprintf("\r\n[SYSTEM] Process \"%s (%d)\" exited with code %d\r\n", p->name, p->proc_index, m.i1);
				//TODO: keep process in zombie state until parent calls wait, so the exit value can be retrieved
				end_process(p);
				break;

			case SYSCALL_PROCESS_OVERVIEW:
				response = process_overview();
				break;

			case SYSCALL_FORK:
				kprintf("in system.c ");
				response = fork_proc(p);
				m.i1 = 0;
				winix_send(who, &m);


				//send 0 to child process
				// kprintf("send 0 to child %d, curr %d",response,who);
				// who = response;
				// m.i1 = 0;
				// winix_sendonce(who,&m);

				break;

			case SYSCALL_FORK_PID:
			 	response = fork_proc(get_proc(m.i1));
				m.i1 = response;
				winix_send(who,&m);
				break;

			case SYSCALL_EXEC:
				response = exec_read_srec(get_proc(who));
				break;

			case SYSCALL_SBRK:
				sptr = (size_t *)_sbrk(m.s1);
				m.p1 = sptr;
				winix_send(who, &m);
				break;

			case SYSCALL_MALLOC:
				sptr = (size_t *)proc_malloc(m.s1);
				m.p1 = sptr;
				winix_send(who, &m);
				break;

			case SYSCALL_FREE:
				proc_free(who);
				break;

			case SYSCALL_HOLE_OVERVIEW:
				hole_list_overview();
				break;

			case SYSCALL_PUTC:
				kputc(m.i1);
				break;

			//System call number is unknown, or not yet implemented.
			default:
				kprintf("\r\n[SYSTEM] Process \"%s (%d)\" performed unknown system call %d\r\n", p->name, p->proc_index, m.type);
				end_process(p);
				break;
		}
		// currpro->ticks_left = 1;
		// if (m.type == SYSCALL_FORK ) {
		// 	while(1){
		// 		counter++;
		// 		curr = ready_q[3][0];
		// 		if(currpro != NULL && !currpro->flags) {
		// 			//Accounting
		// 			//kprintf("sched before %s(%d),pc %x, rbase %x, sp %x\n",current_proc->name,current_proc->proc_index,current_proc->rbase,current_proc->sp );
		// 			currpro->time_used++;
		// 			// if (current_proc->proc_index == 3) {
		// 			// 	kprintf("shell time left %d next %d ",current_proc->ticks_left,current_proc->next == NULL ? -1 : current_proc->next->proc_index);
		// 			// }
		// 			kprintf("curr %d ",currpro->proc_index);
		// 			currpro->ticks_left = 1;
		// 			// while (curr != NULL) {
		// 			// 	kprintf("%d next %d ",curr->proc_index, (curr->next)->proc_index);
		// 			// 	curr = curr->next;
		// 			// }
		// 			//If there's still time left, reduce timeslice and add it to the head of its priority queue
		// 			if(--currpro->ticks_left) {
		// 				enqueue_head(ready_q[currpro->priority], currpro,0);
		//
		// 					kprintf(",%d added to head queue \n",currpro->proc_index);
		// 					//process_overview();
		//
		// 			}
		// 			else { //Re-insert process at the tail of its priority queue
		// 				enqueue_tail(ready_q[currpro->priority], currpro);
		//
		// 				 	kprintf(",%d added to tail queue \n",currpro->proc_index);
		// 					//process_overview();
		//
		// 			}
		// 		}
		//
		// 		//Get the next task
		// 		currpro = pick_proc();
		//
		// 			kprintf(" %d picked \n",currpro->proc_index);
		// 			process_overview();
		// 			if (counter >=3) {
		// 				break;
		// 			}
		// 	}
		//}

	}
}
