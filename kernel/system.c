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
		kprintf("received from %s, call id %d, operation %d\n",p->name,p->proc_index,m.type );
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
				response = fork_proc(p);
				//m.i1 = response;
				//winix_send(who, &m);
				break;
			case SYSCALL_EXEC:
				break;

			case SYSCALL_SBRK:
				sptr = (size_t *)_sbrk(m.s1);
				m.p1 = sptr;
				winix_send(who, &m);
				break;

			case SYSCALL_MALLOC:
				sptr = (size_t *)_malloc(m.s1);
				m.p1 = sptr;
				winix_send(who, &m);
				break;

			case SYSCALL_FREE:
				_free(m.p1);
				break;

			case SYSCALL_HOLE_OVERVIEW:
				hole_list_overview();
				break;

			case SYSCALL_PUTC:
				
				kputc(m.i1);
				winix_send(who,&m);
				break;

			//System call number is unknown, or not yet implemented.
			default:
				kprintf("\r\n[SYSTEM] Process \"%s (%d)\" performed unknown system call %d\r\n", p->name, p->proc_index, m.type);
				end_process(p);
				break;
		}
	}
}
