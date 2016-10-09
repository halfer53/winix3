/**
 * Main entry point for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include "winix.h"

/**
 * Print an error message and lock up the OS... the "Blue Screen of Death"
 *
 * Side Effects:
 *   OS locks up.
 **/
void panic(const char* message) {
	printf("\r\nPanic! ");
	printf(message);

	while(1) {
		RexParallel->Ctrl = 0;
		RexParallel->LeftSSD = 0x79;  //E
		RexParallel->RightSSD = 0x50; //r
	}
}

/**
 * Asserts that a condition is true.
 * If so, this function has no effect.
 * If not, panic is called with the appropriate message.
 */
void assert(int expression, const char *message) {
	if(!expression) {
		printf("\r\nAssertion Failed");
		panic(message);
	}
}

/**
 * Entry point for WINIX.
 **/
void main() {
	//Temp variable for initialising processes.
	proc_t *p = NULL;

	//Print boot message.
	printf("\r\nWINIX v%d.%d\r\n", MAJOR_VERSION, MINOR_VERSION);

	//scan memory, initialise FREE_MEM_BEGIN and FREE_MEM_END
	Scan_FREE_MEM_BEGIN();

	//Set up process table
	init_proc();

	//Initialise the system task
	p = new_proc(system_main, SYSTEM_PRIORITY, "SYSTEM");
	assert(p != NULL, "Create sys task");
	p->quantum = 64;

	//Idle Task
	p = new_proc(idle_main, IDLE_PRIORITY, "IDLE");
	assert(p != NULL, "Create idle task");


	//TODO: The following should be loaded by init.

	//###########################################
	//Shell
	p = new_proc(shell_main, USER_PRIORITY, "Shell");
	assert(p != NULL, "Create shell task");
	p->quantum = 2;

	//Rocks game
	/*p = new_proc(rocks_main, USER_PRIORITY, "Rocks");
	assert(p != NULL, "Create rocks task");
	p->quantum = 4;*/

	//Parallel test program
	p = new_proc(parallel_main, USER_PRIORITY, "Parallel");
	assert(p != NULL, "Create parallel task");
	p->quantum = 1;
	//###########################################


	//Initialise exceptions
	init_exceptions();

	//Kick off first task. Note: never returns.
	sched();
}
