/**
 * evaluation.h
 * jaH
 * 4 Nov 2002
 *
 * Static board evaluation.
 *
 * The evaluate_Static function determines the score for the current
 * board without looking ahead. It does this based on factors
 * determined by the implementation. This is one place where the
 * implementation is all too important.
 *
 * Evaluation is always performed from the side of the tiger.  So, the
 * loss of shikaars are give positive scores and the blocking of
 * tigers are expected to give negative scores.
 *
 * When all the tigers are locked, the score is equal to -infty and
 * when there are more than 9 shikaars taken the score is equal to
 * +infty.
 */

#ifndef bagchal_engine_evaluation_h
#define bagchal_engine_evaluation_h

#include "Board.h"

/**
 * These INFINITY values are used to decide end of games.
 */

#define EVAL_POS_INFTY ( 30000)
#define EVAL_NEG_INFTY (-EVAL_POS_INFTY)

int evaluate_Static (Board_t);

#endif // bagchal_engine_evaluation_h
