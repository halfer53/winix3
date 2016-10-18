#include <sys/rex.h>

/**
 * Writes a character to serial port 1.
 **/
int sys_putc(const int c) {
	//TODO: buffer output and print via system calls.
	while(!(RexSp1->Stat & 2));
	RexSp1->Tx = c;
	return 0;
}

/**
 * Reads a character from serial port 1.
 **/
int sys_getc() {
	//TODO: user interrupt-driven I/O
	while(!(RexSp1->Stat & 1));
	return RexSp1->Rx;
}
