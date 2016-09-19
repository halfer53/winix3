/**
 * Exception-handling routines for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

//System uptime, in ticks.
extern int system_uptime;

/**
 * Initialises Exception Handlers and configures timer.
 **/
void init_exceptions();

#endif
