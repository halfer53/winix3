/**
 * WINIX System Calls.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include <sys/ipc.h>
#include <sys/syscall.h>

/**
 * Get the system uptime.
 **/
int sys_uptime() {
	int response = 0;
	message_t m;

	m.type = SYSCALL_UPTIME;
	response = winix_sendrec(SYSTEM_TASK, &m); //TODO: error checking
	return m.i1;
}

/**
 * Exits the current process.
 **/
int sys_exit(int status) {
	int response = 0;
	message_t m;

	m.type = SYSCALL_EXIT;
	m.i1 = status;
	response = winix_sendrec(SYSTEM_TASK, &m); //TODO: error checking
	return m.i1;
}

int sys_process_overview(){
	int response = 0;
	message_t m;

	m.type = SYSCALL_PROCESS_OVERVIEW;
	response = winix_send(SYSTEM_TASK, &m); //TODO: error checking
	printf("finished system call\r\n" );
	return 0;
}
