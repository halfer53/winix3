/**
 * Simple shell for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include <sys/syscall.h>
#include <stdio.h>
#include <stddef.h>

#define BUF_LEN		100

//Prototypes
int ps(int argc, char **argv);
int uptime(int argc, char **argv);
int shutdown(int argc, char **argv);
int exit(int argc, char **argv);
int fork(int argc, char **argv);
int exec(int argc, char **argv);
int generic(int argc, char **argv);

//Input buffer & tokeniser
static char buf[BUF_LEN];
static char *tokens[BUF_LEN / 2];

//Maps strings to function pointers
struct cmd {
	char *name;
	int (*handle)(int argc, char **argv);
};

//Command handling
struct cmd commands[] = {
	{ "uptime", uptime },
	{ "shutdown", shutdown },
	{ "exit", exit },
	{ "ps", ps },
	{ "fork", fork },
	{ "exec", exec },
	{ NULL, generic }
};
//TODO: ps/uptime/shutdown should be moved to separate programs.

/**
 * Returns true if c is a printable character.
 **/
int isPrintable(int c) {
	return ('!' <= c && c <= '~');
}


int exec(int argc, char **argv){

}

int fork(int argc, char **argv){
	int forkid = 0;
	forkid = sys_fork();
	return 0;
}

int ps(int argc, char **argv){
	return sys_process_overview();
}

/**
 * Prints the system uptime
 **/
int uptime(int argc, char **argv) {
	int ticks, days, hours, minutes, seconds;

	ticks = sys_uptime();
	seconds = ticks / 60; //TODO: define tick rate somewhere
	minutes = seconds / 60;
	hours = minutes / 60;
	days = hours / 24;

	seconds %= 60;
	minutes %= 60;
	hours %= 24;
	ticks %= 100;

	printf("Uptime is %dd %dh %dm %d.%ds\r\n", days, hours, minutes, seconds, ticks);
	return 0;
}

/**
 * Shuts down OS.
 **/
int shutdown(int argc, char **argv) {
	printf("Placeholder for SHUTDOWN\r\n");
	return 0;
}

/**
 * Exits the terminal.
 **/
int exit(int argc, char **argv) {
	printf("Bye!\r\n");
	return sys_exit(0);
}

/**
 * Handles any unknown command.
 **/
int generic(int argc, char **argv) {
	//Quietly ignore empty file paths
	if(argc == 0)
		return 0;

	//TODO: fork/exec program at argv[0]

	printf("Unknown command '%s'\r\n", argv[0]);
	return -1;
}

void shell_main() {
	int i, j;
	int argc;
	char *c;
	struct cmd *handler = NULL;

	while(1) {
		printf("WINIX> ");

		//Read line from terminal
		for(i = 0; i < BUF_LEN - 1; i++) {
			buf[i] = getc(); 	//read

			if(buf[i] == '\r') { //test for end
				break;
			}
			putc2(buf[i]);
			putc(buf[i]); 		//echo
		}
		buf[++i] = '\0';
		printf("\r\n");

		//Tokenise command
		//TODO: proper parsing of arguments
		argc = 0;
		c = buf;
		while(*c) {

			//Skip over non-alphanumeric characters
			while(*c && !isPrintable(*c))
				c++;

			//Add new token
			if(*c != '\0') {
				tokens[argc++] = c;
			}

			//Skip over alphanumeric characters
			while(*c && isPrintable(*c))
				c++;

			if(*c != '\0') {
				*c++ = '\0';
			}
		}

		//Decode command
		handler = commands;
		while(handler->name != NULL && strcmp(tokens[0], handler->name)) {
			handler++;
		}

		//Run it
		handler->handle(argc, tokens);
	}
}
