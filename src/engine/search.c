/**
 * search.c
 * jaH, March 2003
 * 
 * Implements search in search.h
 */

#include "evaluation.h"
#include "search.h"
#include "MoveList.h"
#include "generator.h"
#include "hash.h"

/**
 * Evaluates the board from the perspective 
 * of the side to move.
 */
static int evaluate (Board_t b);

/**
 * Probes the hash table for a board at the given 
 * depth, alpha and beta parameters. The evaluation 
 * is returned in eval if the probing was successful.
 *
 * returns 0 - proving sucessful,
 * -1 - no evaluation retrieved.
 * 
 */
static int 
probe_hash (Board_t, int depth, 
		int alpha, int beta, int * eval);

/**
 * Records an entry into the hash table replacing the previous
 * entry, for the given board at the given board with the
 * given evaluation.
 */
static void record_hash (Board_t, int depth, int eval, int hFlag);

/**
 * Evaluates the board using alpha-beta search.
 */
static int alphabeta 
(Board_t b, int depth, int alpha, int beta);

int search (Board_t board, int depth, pMove_t pmove)
{
	pMoveList_t next_moves = generateUniqueNextMoves (board);
	pMoveList_t best_moves = createEmpty_MoveList ();
	int max_evaluation = EVAL_NEG_INFTY;
	while (next_moves != NULL)
	{
		pMoveList_t move_node = popFrontNode_MoveList (&next_moves);
		Move_t move = move_node->move;
		destroy_MoveList (&move_node);
		Board_t new_board = transform_Move (board, move);
		int evaluation = -alphabeta (new_board, depth, 
					EVAL_NEG_INFTY, EVAL_POS_INFTY);
		if (evaluation > max_evaluation) 
		{
			max_evaluation = evaluation;
			destroy_MoveList (&best_moves);
			best_moves = createSingleNode_MoveList (move);
		}
		else if (evaluation == max_evaluation)
		{
			best_moves = 
			join_MoveList (best_moves,
					createSingleNode_MoveList (move));
		}
	}
	*pmove = getRandomMove (best_moves);
	destroy_MoveList (&best_moves);
	Turn_t turn = getTurn_Board (board);
	if (turn == TURN_T_TIGER) return max_evaluation;
	else return -max_evaluation;
}

static int evaluate (Board_t b)
{
	Turn_t turn = getTurn_Board (b);
	if (turn == TURN_T_TIGER) return evaluate_Static (b);
	else return -evaluate_Static (b);
}


static int alphabeta 
(Board_t b, int depth, int alpha, int beta)
{
	int hashF = EVAL_FLAG_ALPHA;
	int eval;
	pMoveList_t next_moves;
	
	// probe hash table.
	if ( probe_hash (b, depth, alpha, beta, &eval) == 0 )
		return eval;
	
	// hash probing failed.
	next_moves = generateUniqueNextMoves (b);
	if (depth <= 0 || next_moves == NULL) 
	{
	        if (next_moves == NULL) eval = EVAL_NEG_INFTY;
		else eval = evaluate (b);
		record_hash (b, depth, eval, EVAL_FLAG_EXACT);
		destroy_MoveList (&next_moves);
		return eval;
	}
	
	// depth > 0	
	while (next_moves != NULL)
	{
		pMoveList_t move_node 
			= popFrontNode_MoveList (&next_moves);
		Move_t move = move_node->move;
		destroy_MoveList (&move_node);
		Board_t new_board = transform_Move (b, move);
		eval = -alphabeta (new_board, depth-1, 
					-beta, -alpha);
		if (eval >= beta)
		{
			destroy_MoveList (&next_moves);
			record_hash (b, depth, 
					beta, EVAL_FLAG_BETA);
			return beta;
		}
		if (eval > alpha)
		{
			hashF = EVAL_FLAG_EXACT;
			alpha = eval;
		}
	}
	record_hash (b, depth, alpha, hashF);
	return alpha;
}

int probe_hash (Board_t b, int depth, int alpha, int beta, int * eval)
{
	ZKey_t zk = zobrist_board (b);
	HashElem_t hE = getHashElement (zk);
	
	// check if hashed board present.
	if (hE.flags == HASH_FLAG_EMPTY || hE.board != b)
		return -1; // board not present in hash
	
	if (hE.depth >= depth)
	{
		if (hE.flags == EVAL_FLAG_EXACT) 
		{
			*eval = hE.eval;
			return 0;
		}
		if ((hE.flags == EVAL_FLAG_ALPHA) &&
		    (hE.eval <= alpha)) 
		{
			*eval = alpha;
			return 0;
		}
		if ((hE.flags == EVAL_FLAG_BETA) &&
		    (hE.eval >= beta)) 
		{
			*eval = beta;
			return 0;
		}
	}
	return -1;
}


void record_hash (Board_t b, int depth, int eval, int hFlag)
{
	Move_t m;
	ZKey_t zk = zobrist_board (b);
	HashElem_t hE = create_HashElement 
				(b, depth, hFlag, eval, m);
	setHashElement (zk, hE);
}
