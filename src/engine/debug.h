/**
 * Debug.h
 * Date: 4 Aug 2002
 * Author: jaH
 *
 * Define debug constants. This file defines debug levels. The
 * higher the level, the less time-optimum code is used to
 * self-check and destruct (through assert[ions]). If a higher
 * debug level is defined, all others should also be defined.
 */
#ifndef bagchal_engine_debug_h
#define bagchal_engine_debug_h

#define DEBUG_LEVEL_2
#define DEBUG_LEVEL_1

#ifdef DEBUG_LEVEL_1

void print_bits (i64_t r)
{
	unsigned char i;
	for ( i = 63; ; i-- ) {
		unsigned int j;
		j = r >> i;
		j &= 0x1;
		printf ("%d", j);
		if (i == 0) break;
	}
}

#endif // DEBUG_LEVEL_1

#endif
