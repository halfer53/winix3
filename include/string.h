/**
 * A rather limited version of <string.h>
 *
 * Revision History:
 *  2016-09-19		Paul Monigatti			Original
 **/

#ifndef _STRING_H_
#define _STRING_H_

int strcmp(const char *s1, const char *s2);
int strlen(const char *s);
char *strcpy(char *dest,const char *src);
char *strcat(char *dest, const char *src);

#endif
