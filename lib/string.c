#include <string.h>

/**
 * Compares two strings.
 **/
int strcmp(const char *s1, const char *s2) {
	while(*s1 && *s2) {
		if(*s1 != *s2) {
			break;
		}
		s1++;
		s2++;
	}
	
	return *s1 - *s2;
}

/**
 * Calculates the length of a string.
 **/
int strlen(const char *s) {
	int len = 0;
	
	while(*s++) {
		len++;
	}
	
	return len;
}
