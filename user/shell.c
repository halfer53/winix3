/**
 * Simple shell for WINIX.
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#include <sys/syscall.h>
#include <stdio.h>
#include <stddef.h>
#include <type.h>
#include <size.h>

#define BUF_LEN		100

//Prototypes
int ps(int argc, char **argv);
int uptime(int argc, char **argv);
int shutdown(int argc, char **argv);
int exit(int argc, char **argv);
int shell_fork(int argc, char **argv);
int shell_exec(int argc, char **argv);
int testmalloc(int argc, char **argv);
int generic(int argc, char **argv);
#define my_sizeof(var) (char *)(&var+1)-(char*)(&var)

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
	{ "fork", shell_fork },
	{ "exec", shell_exec },
	{ "testmal", testmalloc},
	{ NULL, generic }
};
//TODO: ps/uptime/shutdown should be moved to separate programs.

/**
 * Returns true if c is a printable character.
 **/
int isPrintable(int c) {
	return ('!' <= c && c <= '~');
}

int testmalloc(int argc, char **argv){
	size_t a = 0;
	char b = 'a';
	int c = 0;
	long d = 0;
	size_t *ap = NULL;
  char *bp = NULL;
	int *cp = NULL;
	char **lines = NULL;
	int n = 2;
	char **prev_p = NULL;
	char *prev_p_line[2] = {NULL,NULL};
	int i = 0;

	if ((lines = (char **)malloc(n*POINTER_SIZE)) == NULL) {
		printf("not enough space\n");
		return 0;
	}else{
		printf("lines point at addr %x\n", lines);
		prev_p = lines;
	}
	for ( i = 0; i < n; i++) {
		if ((lines[i] = (char *)malloc(CHAR_SIZE * 10)) == NULL) {
			printf("not enough space\n");
			return 0;
		}
		prev_p_line[i] = lines[i];
		printf("lines[%d] point at addr %x\n",i, lines);
	}

	strcpy(lines[0],"a");
	strcpy(lines[1],"ab");

	for ( i = 0; i < n; i++) {
		printf("line %d content %s\n",i,lines[i] );
	}

	for ( i = 0; i < n; i++) {
		free(lines[i]);
	}
	free(lines);
	return 0;

	if ((lines = (char **)malloc(n*POINTER_SIZE)) == NULL) {
		printf("not enough space\n");
		return 0;
	}else{
		if (prev_p != lines) {
			printf(" incorrect free, new addr at %x, old addr at %x\n",lines,prev_p );

		}
	}
	for ( i = 0; i < n; i++) {
		if ((lines[i] = (char *)malloc(CHAR_SIZE * 10)) == NULL) {
			printf("not enough space\n");
			return 0;
		}
		if (prev_p_line[i] != lines[i]) {
			printf(" incorrect free, new addr at %x, old addr at %x\n",lines[i],prev_p_line[i] );

		}

	}



	// printf("unsigned long %d\n",my_sizeof(a) );
	 printf("char pointer size %d\n",my_sizeof(bp) );
	// printf("int %d\n",my_sizeof(c) );
	// printf("long %d\n",my_sizeof(d) );

 	ap =	(size_t *)malloc(SIZE_T_SIZE);
	*ap = 1;
	printf("size_t malloced ap addr %d, val %d\n",ap,*ap);

	bp = (char *)malloc(CHAR_SIZE);
	*bp = 'b';
	printf("char malloced ap addr %d, val %c\n",bp,*bp);
	printf("size_t malloced ap addr %d, val %d\n",ap,*ap);

	free(ap);
	printf("free size_t\n");
	printf("char malloced ap addr %d, val %c\n",bp,*bp);
	printf("size_t malloced ap addr %d, val %d\n",ap,*ap);
	return 0;
}

int shell_exec(int argc, char **argv){

	return 0;
}
int shell_fork(int argc, char **argv){
	int forkid = 0;
	forkid = fork();
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
			//printf2("%d\n",(int)buf[i] );
			if(buf[i] == '\r') { //test for end
				break;
			}
			if ((int)buf[i] == 8) { //backspace

				if (i != 0) {
					putc(buf[i]);
					i--;
				}
				i--;
				continue;
			}

			putc(buf[i]); 		//echo
		}
		buf[++i] = '\0';
		printf("\r\n" );

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
