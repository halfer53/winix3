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
	return m.m_u.m_m1.m1i1;
}

/**
 * Exits the current process.
 **/
int sys_exit(int status) {
	int response = 0;
	message_t m;

	m.type = SYSCALL_EXIT;
	m.m_u.m_m1.m1i1 = status;
	response = winix_sendrec(SYSTEM_TASK, &m); //TODO: error checking
	return m.m_u.m_m1.m1i1;
}

int sys_process_overview(){
	int response = 0;
	message_t m;

	m.type = SYSCALL_PROCESS_OVERVIEW;
	response = winix_send(SYSTEM_TASK, &m); //TODO: error checking
	return 0;
}

int sys_fork(){
	int response = 0;
	message_t m;

	m.type = SYSCALL_FORK;
	response = winix_send(SYSTEM_TASK, &m); //TODO: error checking
	return 0;
}

int sys_exec(char* lines[],int length){
	int response = 0;
	message_t m;

	m.type = SYSCALL_FORK;
	response = winix_send(SYSTEM_TASK, &m); //TODO: error checking
	return 0;
}

void *sbrk(unsigned long size){
	int response = 0;
	message_t m;

	m.type = SYSCALL_SBRK;
	m.m_u.m_m2.m2ul1 = size;
	response = winix_send(SYSTEM_TASK, &m);
	return 0;
	//return m.m_u.m_m2.m2p1;
}
