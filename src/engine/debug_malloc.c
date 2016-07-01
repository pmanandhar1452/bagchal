/**
 * debug_malloc.c
 * 14 Dec 2002
 * jah and ram
 *
 * Malloc and Free with print to stdout for debugging.
 * 
 */

#include <stdlib.h>
#include "debug.h"

void * 
malloc_debug (size_t size) {

	void * mem;

#ifdef DEBUG_LEVEL_2
	printf ("Inside Malloc.. Allocating %d bytes ", size);
#endif
	mem = malloc (size);
#ifdef DEBUG_LEVEL_2
	printf ("at location %x.\n", mem);
#endif

	return mem;
}

void free_debug (void *pMem) {

#ifdef DEBUG_LEVEL_2
	printf ("Inside Free.. Deallocating location: %x.\n", pMem);
#endif
	free (pMem);

}

