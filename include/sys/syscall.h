/**
 * Userspace system call library for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/**
 * System Call Numbers
 **/
#define SYSCALL_GETC		1
#define SYSCALL_HOLE_OVERVIEW		2
#define SYSCALL_PS			3
#define SYSCALL_UPTIME		4
#define SYSCALL_EXIT		5
#define SYSCALL_PROCESS_OVERVIEW		6
#define SYSCALL_FORK		7
#define SYSCALL_EXEC    8
#define SYSCALL_LOAD_SREC    9
#define SYSCALL_SBRK    10
#define SYSCALL_MALLOC    11
#define SYSCALL_FREE    12
#define SYSCALL_PUTC    13
//TODO: create a sensible allocation scheme for system call numbers

/**
 * Returns the current system uptime, specified as the number of ticks since boot.
 **/
int sys_uptime();

/**
 * Exits the current process.
 **/
int sys_exit(int status);
int sys_process_overview();
int fork();
int exec(char* lines[],int length);


int sys_process_overview();

int sys_fork();

int sys_exec(char* lines[],int length);

void *sbrk(unsigned long size);

void *_malloc(unsigned long size);
void _free(void *ptr_parameter);
void hole_list_overview();

#endif
