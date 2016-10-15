/**
 * WINIX Library.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#ifndef _WINIX_IPC_H_
#define _WINIX_IPC_H_

/**
 * The message structure for IPC
 **/
typedef struct {
	int src;
	int type;
	int i1, i2, i3;
	void *p1, *p2, *p3;
	unsigned long s1;
} message_t;

/**
 * Magic Numbers for send/receive
 **/
#define WINIX_SEND		0x13370001
#define WINIX_RECEIVE	0x13370002
#define WINIX_SENDREC	0x13370003

/**
 * Boot Image Task Numbers
 **/
#define SYSTEM_TASK 0


/**
 * Sends a message to the destination process
 **/
int winix_send(int dest, message_t *m);

/**
 * Receives a message.
 **/
int winix_receive(message_t *m);

/**
 * Sends and receives a message to/from the destination process.
 *
 * Note: overwrites m with the reply message.
 **/
int winix_sendrec(int dest, message_t *m);

#endif
