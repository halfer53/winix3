/**
 * WINIX Library.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#ifndef _WINIX_IPC_H_
#define _WINIX_IPC_H_
typedef struct {int m1i1, m1i2, m1i3; void *m1p1, *m1p2, *m1p3;} mess_1;
typedef struct {int m2i1, m2i2, m2i3; long m2l1;unsigned long m2ul1; void *m2p1; short m2s1;} mess_2;
/**
 * The message structure for IPC
 **/
typedef struct {
	int src;
	int type;
	union{
		mess_1 m_m1;
    mess_2 m_m2;
	}m_u;
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
