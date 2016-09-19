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
#define SYSCALL_GETC1		1
#define SYSCALL_GETC2		2
#define SYSCALL_PS			3
#define SYSCALL_UPTIME		4
#define SYSCALL_EXIT		5
//TODO: create a sensible allocation scheme for system call numbers

/**
 * Returns the current system uptime, specified as the number of ticks since boot.
 **/
int sys_uptime();

/**
 * Exits the current process.
 **/
int sys_exit(int status);

#endif
