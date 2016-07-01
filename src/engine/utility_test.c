/**
 * Tests for utility.h
 *
 * date: 27 july 2002
 * authors: jaH and suraj
 */

#include "utility.h"

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

int main ()
{
	unsigned char i;
	i64_t r;
	printf ("sizeof (i64_t) == %d\n", 
			sizeof (i64_t) );
	printf ("binary of 37: ");
	print_bits ( (i64_t)37 );
	printf ("\n");
	for ( i = 0; i < 100; i++ ) {
		printf ( "%d : ", i );
		r = generateMask_i64_t (i);
		print_bits (r);
		printf ("\n");
	}
	return 0;
}
				
