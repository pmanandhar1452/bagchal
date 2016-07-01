/**
 * test_utility.h
 * 4 Nov 2002
 * jaH
 * 
 * Some utility functions used for testing.
 */


#ifndef bagchal_engine_test_utility_h
#define bagchal_engine_test_utility_h

#include "MoveList.h"

void print_move ( Move_t );
void print_move_list ( pMoveList_t );
void print_move_node ( pMoveList_t );
void print_board ( Board_t );
Board_t getInitialBoard ();

#endif // bagchal_engine_test_utility_h
