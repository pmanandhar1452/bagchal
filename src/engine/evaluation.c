/**
 * evaluation.c
 * 5 Nov 2002
 * jaH
 *
 * =============== Change Log =========================
 *
 * 2 April 2003
 * Added evaluation factor Nia, Nth for inaccessible cells.
 *
 * New formula = K*Nk*Nk - D*Nb*Nb - M*Nia*Nia + T*Nth*Nth
 * setting M = 7, K=7, D=7, T=1
 * 
 * ====================================================
 * 
 * Implementation of evaluation.h
 *
 * In this implementation I have decided to take just two factors into
 * account. The number of shikaar killed (call that Nk) and the number
 * of tigers blocked (call that Nb). The evaluation formula will be
 * highly non-linear (exponential) in terms of the two parameters.
 *
 * I am guessing that exponential is a nice evalutation formula
 * because, for example, blocking 1 or even 2 tigers is not a terribly
 * advantegeous thing in itself, for the shikaar, but blocking all 4
 * tigers, wins the game.
 *
 * Also, I only considered the two most obvious factors and left out
 * others such as control of the center, etc. delibrately so that the
 * system would not be handicapped by any unproven theories.
 *
 * The current formula used to calculate the static evaluation (E) is
 *
 * E = K^Nk - D^Nb 
 *
 * trying K = 3, D = 9, since this gives approximately equal marks
 * for killing 6 shikaar as to blocking 3 tigers.
 */

#include "evaluation.h"
#include "generator.h"
#include <math.h>
#include <stdlib.h>

static int getNumTigersBlocked (Board_t board);
static int getNumTigersList (pMoveList_t);
static int getNumInAccessible (Board_t);
static void initAccMat (Board_t b, Boolean_t [5][5]);
static int countAccMat (Board_t b, Boolean_t [5][5]);
static void accMatFlagNeighbors (Board_t, Boolean_t [5][5], Boolean_t *, int, int);
static int getNumThreatened (Board_t);

#define K 7
#define D 7
#define M 7
#define T 1

int 
evaluate_Static (Board_t board)
{

  int Nk, Nb, Nia, Nth;
  double E;

  Nb = getNumTigersBlocked (board);
  if (Nb == 4)
    return EVAL_NEG_INFTY;

  Nk = getNumberOfShikaarKilled_Board (board);
  if (Nk > 6) return EVAL_POS_INFTY;
  
  Nia = getNumInAccessible (board);
  Nth = getNumThreatened (board);
  
  E = K*Nk*Nk - D*Nb*Nb - M*Nia*Nia + Nth*Nth; 
  
  if (E < EVAL_NEG_INFTY)
    return EVAL_NEG_INFTY;
  else if (E > EVAL_POS_INFTY)
    return EVAL_POS_INFTY;
  else
    return (int)E;

}


int
getNumTigersBlocked (Board_t board)
{

  pMoveList_t list;
  int num_t;
  Board_t b1;
  b1 = copyBoard (board);
  setTurn_Board (&b1, TURN_T_TIGER);

  list = generateUniqueNextMoves (b1);
  num_t = getNumTigersList (list);
  destroy_MoveList (&list);
  return (4 - num_t);

}

int 
getNumTigersList (pMoveList_t list)
{

  int x[4];
  int y[4];
  int num;
  int i;
  Boolean_t match;

  pMoveList_t r;

  num = 0;
  for (
       r = list;
       (r != NULL) && (num < 4);
       r = r->pnext
       )
    {

      x[num] = getStartX_Move (r->move);
      y[num] = getStartY_Move (r->move); 

      match = FALSE;
      for (i = 0; i < num; i++)
        {
          if (
              (x[num] == x[i]) &&
              (y[num] == y[i])
              )
            {
              match = TRUE;
              break;
            }
        }
      if (!match) 
        {
          num++;
        }
    }

  return num;

}

/**
 * Determine the number of inaccessible squares in a board.
 *
 * Algorithm:
 *
 * 1. Mark all squares that contain tigers.
 * 2. Iterate until no further squares are marked in last iteration.
 * 	1. If a square is marked, and a tiger placed in that
 * 	square can move to an unmarked square, mark the unmaked
 * 	square.
 * 
 */
int getNumInAccessible (Board_t b)
{
	Boolean_t accMat [5][5] = 
	{ { FALSE, FALSE, FALSE, FALSE, FALSE },
	  { FALSE, FALSE, FALSE, FALSE, FALSE },
	  { FALSE, FALSE, FALSE, FALSE, FALSE },
	  { FALSE, FALSE, FALSE, FALSE, FALSE },
	  { FALSE, FALSE, FALSE, FALSE, FALSE } };

        Boolean_t changed;

	initAccMat (b, accMat);
	
	do
	{
		int i, j;
		changed = FALSE;
		for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			if (accMat[i][j] == TRUE)
			{
				accMatFlagNeighbors (b, accMat, &changed, i, j);
			}
	} while (changed);
	return countAccMat (b, accMat);
}

void initAccMat (Board_t b, Boolean_t accMat[5][5])
{
	int i, j;
	for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
		if (getPieceAtPosition_Board (b, i, j) == PIECE_T_TIGER)
			accMat[i][j] = TRUE;
}

int countAccMat (Board_t b, Boolean_t accMat[5][5])
{
	int i, j, n = 0;
	for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
		if (accMat[i][j] == FALSE 
		    && getPieceAtPosition_Board (b, i, j) 
		    	!= PIECE_T_SHIKAAR
		    ) 
			n++;
	return n;
}

void accMatFlagNeighbors (Board_t b, Boolean_t accMat[5][5], 
			Boolean_t *changed, int x, int y)
{
	Board_t tb;
	int dir, fx, fy;
	for ( dir = MOVE_DIR_T_P0;
	      dir <= MOVE_DIR_T_PN;
	      dir++
	     )
	{
		Move_t m = create_Move (MOVE_T_TIGER_NORMAL, x, y, dir);
		tb = copyBoard (b);
		setPieceAtPosition_Board (&tb, PIECE_T_TIGER, x, y);
		if (isValid_Move_noCheckBoard (tb, m))
		{
			fx = getFinalX_Move (m);
			fy = getFinalY_Move (m);
			if (accMat[fx][fy] == FALSE)
			{
				accMat[fx][fy] = TRUE;
				*changed = TRUE;
			}
		}
		
		m = create_Move (MOVE_T_TIGER_TAKE, x, y, dir);
		if (isValid_Move_noCheckBoard (tb, m))
		{
			fx = getFinalX_Move (m);
			fy = getFinalY_Move (m);
			if (accMat[fx][fy] == FALSE)
			{
				accMat[fx][fy] = TRUE;
				*changed = TRUE;
			}
		}
	}
}


int getNumThreatened (Board_t b)
{
	int i, j, n = 0;
	for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
	if (getPieceAtPosition_Board (b, i, j) == PIECE_T_TIGER)
	{
		int dir;
		for (dir = MOVE_DIR_T_P0;
		     dir <= MOVE_DIR_T_PN;
		     dir++)
		{
			Move_t m = create_Move (MOVE_T_TIGER_TAKE, i, j, dir);
			if (isValid_Move_noCheckBoard (b, m)) n++;
		}
	}
	return n;
}
