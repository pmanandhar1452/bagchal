/**
 * Implementation for utility.h
 *
 * date: 27 july 2002
 * authors: jaH and suraj
 */

#include "utility.h"

i64_t 
generateMask_i64_t ( unsigned char pos )
{
	if ( pos > 63 ) return 0;
	else {
		return (((i64_t)1) << pos);
	}
}
