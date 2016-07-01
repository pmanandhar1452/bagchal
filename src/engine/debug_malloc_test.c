/**
 * debug_malloc_test.c
 * 14 Dec 2002
 * jah and ram
 *
 * 
 * 
 */

#include "debug_malloc.h"


int main () {

	char * pChar;
	printf ("Testing Debug malloc!!\n");
	pChar = (char *)malloc_debug (sizeof(char)*5);
	pChar[0] = 'a';
	pChar[1] = 'b';
	pChar[2] = 'a';
	pChar[3] = 'b';
	pChar[4] = 'a';
	//pChar[5] = 'b';
	free_debug (pChar);
	printf ("Tests completed.\n");
	return 0;

}