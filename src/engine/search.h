/**
 * search.h
 * jaH, March 2003
 *
 * Search the best move from the given position.
 * I will implement this in the traditional way, from
 * the minimax approach, with alpha-beta pruning.
 * Or perhaps, we can also experiment with iterative
 * deepening and other techniques. Currently, the
 * only parameter constraining search would be 
 * the maximum depth of search. We can later add timing
 * constraints.
 */

#ifndef bagchal_engine_search_h
#define bagchal_engine_search_h

#include "Board.h"
#include "move.h"


/**
 * Return the best move from the current position in the
 * board given the depth. If the board is invalid, returns
 * 0. The move has to be passed from outside. No memory 
 * allocation is done.
 */
int search (Board_t board, int depth, pMove_t move);

#endif //bagchal_engine_search_h
