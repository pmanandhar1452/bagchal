/**
 * generator.h
 * jaH 
 * 30 Oct 2002
 *
 * Generates the next moves possible given the current board.
 */

#ifndef bagchal_engine_generator_h
#define bagchal_engine_generator_h

#include "MoveList.h"


/**
 * Generate a list of possible next moves according to the rules
 * of BagChaal. If the board is invalid, or if the next move can not 
 * be made for the current turn in the board, the empty list, i.e.
 * NULL is returned.
 *
 * Symmetrical moves are not generated.
 */
pMoveList_t generateUniqueNextMoves (Board_t);

/**
 * Select a random move from a choice of equivalent moves. If the
 * given move is not valid for the givne board, then the same move
 * is returned.
 *
 */
Move_t randomizeMove (Board_t, Move_t);

/**
 * Returns a random move from the given list.
 */
Move_t getRandomMove (pMoveList_t list);

#endif
