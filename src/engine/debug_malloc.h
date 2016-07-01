/**
 * debug_malloc.h
 * 14 Dec 2002
 * jah and ram
 *
 * Malloc and Free with print to stdout for debugging.
 * 
 */

#ifndef bagchal_engine_debug_malloc_h
#define bagchal_engine_debug_malloc_h

void * malloc_debug (size_t);
void free_debug (void *);

#endif