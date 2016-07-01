/**
 * generator.c
 * 1 Nov 2002
 * jaH
 *
 * Implementation for generator.h
 */

#include <assert.h>
#include <stdlib.h>

#include "generator.h"
#include "symmetry.h"

static pMoveList_t generateShikaarMoves (Board_t);
static pMoveList_t generateTigerMoves (Board_t);
static void reduceList ( pMoveList_t *, Board_t );
static void reduceListEquality ( pMoveList_t * );
static pMoveList_t getShikaarPlacedMoves (Board_t);
static pMoveList_t getShikaarMovedMoves (Board_t);
static pMoveList_t getTigerTakes (Board_t);
static pMoveList_t getTigerMoves (Board_t);
static pMoveList_t getShikaarMoved (Board_t, int, int);
static pMoveList_t getTigerTakeAt (Board_t, int, int);
static pMoveList_t getTigerMoveAt (Board_t, int, int);
static Boolean_t symmetricallyEquivalent (Board_t, Move_t, Move_t);

static Move_t getSymmetricalMoveRefYEq2 (Move_t);
static Move_t getSymmetricalMoveRefXEq2 (Move_t);
static Move_t getSymmetricalMoveRefXEqY (Move_t);
static Move_t getSymmetricalMoveRefXEq4MnY (Move_t);
static Move_t getSymmetricalMoveRotClk (Move_t);
static Move_t getSymmetricalMoveRotAntiClk (Move_t);
static Move_t getSymmetricalMoveRotPI (Move_t);


/**
 * Implementation notes:
 *
 * All possible moves are first generated and the moves are then
 * cancelled out depending by checking the symmetries. If there are n
 * moves then it takes O(n*n) steps to check the symmetry. There could
 * be an optimisation possiblity here.
 */
pMoveList_t 
generateUniqueNextMoves (Board_t board) 
{

  pMoveList_t mlist;

  if ( ! isValid_Board ( board ) ) return NULL;

  if (getTurn_Board (board) == TURN_T_SHIKAAR)
    mlist = generateShikaarMoves (board);
  else 
    mlist = generateTigerMoves (board);

  if ( mlist != NULL )
    reduceList ( &mlist, board );
  return mlist;

}

static pMoveList_t 
generateShikaarMoves (Board_t brd) 
{

  if (getNumberOfShikaarLeft_Board (brd) > 0)
    return getShikaarPlacedMoves (brd);
  else 
    return getShikaarMovedMoves (brd);

}

static pMoveList_t 
generateTigerMoves (Board_t brd) 
{

  pMoveList_t mlistMoves, mlistTakes;
  
  mlistTakes = getTigerTakes (brd);
  mlistMoves = getTigerMoves (brd);

  return join_MoveList (mlistTakes, mlistMoves);

}

static pMoveList_t 
getShikaarPlacedMoves (Board_t brd)
{

  int i, j;
  pMoveList_t list;
  Move_t move;

  list = createEmpty_MoveList ();

  // for each empty position on the board 
  // generate a move
  
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      {
        if ( getPieceAtPosition_Board (brd, i, j) 
             == PIECE_T_EMPTY )
          {
            move = create_Move 
              ( MOVE_T_SHIKAAR_PLACED,
                i, j, 0
                );
            list = join_MoveList 
              ( list, createSingleNode_MoveList (move));
          }
      }

  return list;

}

static pMoveList_t
getShikaarMovedMoves (Board_t brd)
{

  int i, j;
  pMoveList_t list;

  list = createEmpty_MoveList ();
  
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      {
        if ( getPieceAtPosition_Board (brd, i, j)
             == PIECE_T_SHIKAAR ) {
          
          list = join_MoveList 
            (list, getShikaarMoved (brd, i, j));
          
          
        }
        
      }

  return list;

}

static pMoveList_t 
getShikaarMoved (Board_t brd, int i, int j)
{

  pMoveList_t list;
  Move_t move;
  unsigned int dir;

  list = createEmpty_MoveList ();
  // for each direction
  for (
       dir = MOVE_DIR_T_P0; 
       dir <= MOVE_DIR_T_PN; 
       dir++ )
    {
      move = create_Move 
        ( MOVE_T_SHIKAAR_MOVED, i, j, dir );

      if ( isValid_Move (brd, move) )
        list = join_MoveList 
          (list, createSingleNode_MoveList (move));
      
    }
  return list;
}

static pMoveList_t 
getTigerTakes (Board_t brd)
{

  pMoveList_t list;
  int i, j;

  list = createEmpty_MoveList ();
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      {
        if ( getPieceAtPosition_Board (brd, i, j)
             == PIECE_T_TIGER ) 
          {
            list = join_MoveList
              ( list, getTigerTakeAt (brd, i, j) );
          }

      }
  return list;
}

static pMoveList_t 
getTigerTakeAt (Board_t brd, int i, int j)
{

  pMoveList_t list;
  Move_t move;
  unsigned int dir;

  list = createEmpty_MoveList ();
  // for each direction
  for (
       dir = MOVE_DIR_T_P0; 
       dir <= MOVE_DIR_T_PN; 
       dir++ )
    {
      move = create_Move 
        ( MOVE_T_TIGER_TAKE, i, j, dir );

      if ( isValid_Move (brd, move) )
        list = join_MoveList 
          (list, createSingleNode_MoveList (move));
      
    }
  return list;
}

static pMoveList_t 
getTigerMoveAt (Board_t brd, int i, int j)
{

  pMoveList_t list;
  Move_t move;
  unsigned int dir;

  list = createEmpty_MoveList ();
  // for each direction
  for (
       dir = MOVE_DIR_T_P0; 
       dir <= MOVE_DIR_T_PN; 
       dir++ )
    {
      move = create_Move 
        ( MOVE_T_TIGER_NORMAL, i, j, dir );

      if ( isValid_Move (brd, move) )
        list = join_MoveList 
          (list, createSingleNode_MoveList (move));
      
    }
  return list;
}

static pMoveList_t 
getTigerMoves (Board_t brd)
{

  pMoveList_t list;
  int i, j;

  list = createEmpty_MoveList ();
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      {
        if ( getPieceAtPosition_Board (brd, i, j)
             == PIECE_T_TIGER ) 
          {
            list = join_MoveList
              ( list, getTigerMoveAt (brd, i, j) );
          }

      }
  return list;
}


/**
 *
 * Algorithm to reduce a list. 
 * This is a home grown algorithm, brewed in as little as
 * a few minutes!!
 *
 * Input [iList] contains list to be reduced
 *
 * 1. Inilialise [checked] to empty.
 * 2. While there are nodes remaining in [iList]
 * 2.1 pop the front node from [iList]
 * 2.2 For each node already in [checked]
 * 2.2.1 check whether the popped node is symmetrically 
 *       eqivalent to node in checked.
 * 2.2.2 if it is destroy the popped node
 * 2.3 If the popped node does not match any other node
 *     in [checked] append the node to checked
 *
 * 3. [checked] contains reduced list.
 */ 
static void
reduceList ( pMoveList_t * iList, Board_t brd )
{

  pMoveList_t checked;
  pMoveList_t check_runner;
  pMoveList_t popped;
  Boolean_t match;

  checked = createEmpty_MoveList ();
  while ( (*iList) != NULL )
    {
      popped = popFrontNode_MoveList (iList);
      match = FALSE;
      for (
           check_runner = checked;
           check_runner != NULL;
           check_runner = check_runner->pnext
           )
        {
          if ( symmetricallyEquivalent 
               (brd, popped->move, check_runner->move)
               )
            {
              match = TRUE;
              break;
            }
        }
      if (match)
        {
          destroy_MoveList (&popped);
        }
      else 
        {
          checked = join_MoveList (checked, popped);
        }
    }

  *iList = checked;
}

static void
reduceListEquality ( pMoveList_t * iList )
{

  pMoveList_t checked;
  pMoveList_t check_runner;
  pMoveList_t popped;
  Boolean_t match;

  checked = createEmpty_MoveList ();
  while ( (*iList) != NULL )
    {
      popped = popFrontNode_MoveList (iList);
      match = FALSE;
      for (
           check_runner = checked;
           check_runner != NULL;
           check_runner = check_runner->pnext
           )
        {
          if ( equals_Move(popped->move, check_runner->move)
               )
            {
              match = TRUE;
              break;
            }
        }
      if (match)
        {
          destroy_MoveList (&popped);
        }
      else 
        {
          checked = join_MoveList (checked, popped);
        }
    }

  *iList = checked;
}

static Boolean_t
symmetricallyEquivalent (Board_t brd, Move_t m1, Move_t m2)
{

  Board_t new_b1, new_b2;

  new_b1 = transform_Move (brd, m1);
  new_b2 = transform_Move (brd, m2);
  
  if (isEqual_Board (new_b1, new_b2))
    return TRUE;

  if (isEquivalent_Symmetry (new_b1, new_b2))
    return TRUE;

  return FALSE;

}

/**
 * Algorithm for randomizing moves.
 *
 *
 * 0. If this is the shikaar placed move at the centre, then
 *    return the same move.
 *
 * 1. Initialise the list of moves to a singleton with
 *    input move.
 *
 * 2. For each symmetry of the board, 
 *
 */
Move_t
randomizeMove (Board_t brd, Move_t move) 
{

  pMoveList_t list;
  Move_t new_move;

  if (!isValid_Move (brd, move))
    return move;

  if (
      (getStartX_Move (move) == 2) &&
      (getStartY_Move (move) == 2) &&
      (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
      )
    return move;

  list = createSingleNode_MoveList (move);
  if ( checkReflectionYEq2_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRefYEq2 (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }
  if ( checkReflectionXEq2_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRefXEq2 (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }
  if ( checkReflectionXEqY_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRefXEqY (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }
  if ( checkReflectionXEq4MnY_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRefXEq4MnY (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }
  if ( checkRotationClockwise_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRotClk (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }
  if ( checkRotationAntiClockwise_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRotAntiClk (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }
  if ( checkRotationPI_Symmetry (brd, brd) )
    {
      new_move = getSymmetricalMoveRotPI (move);
      list = join_MoveList (list, createSingleNode_MoveList (new_move));
    }

  reduceListEquality (&list);
  new_move = getRandomMove (list);
  destroy_MoveList (&list);

  return new_move;

}

Move_t 
getRandomMove (pMoveList_t list)
{
  
  unsigned int num, index;
  unsigned int random;
  pMoveList_t runner;

  assert (list != NULL);

  num = getNodeCount_MoveList (list);
  random = rand ()/(RAND_MAX + 1.0)*num;

  index = 0;
  for (
       runner = list;
       runner != NULL && index != random;
       )
    {
      runner = runner->pnext;
      index++;
    }

  if (runner == NULL)
    return list->move;
  
  return runner->move;
}

static Move_t 
getSymmetricalMoveRefYEq2 (Move_t move)
{

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = getStartX_Move (move);
  starty = 4 - getStartY_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
    switch (getDirection_Move (move))
      {
      case MOVE_DIR_T_PP:
        dir = MOVE_DIR_T_PN;
        break;
      case MOVE_DIR_T_0P:
        dir = MOVE_DIR_T_0N;
        break;
      case MOVE_DIR_T_NP:
        dir = MOVE_DIR_T_NN;
        break;
      case MOVE_DIR_T_NN:
        dir = MOVE_DIR_T_NP;
        break;
      case MOVE_DIR_T_0N:
        dir = MOVE_DIR_T_0P;
        break;
      case MOVE_DIR_T_PN:
        dir = MOVE_DIR_T_PP;
        break;
      default:
        dir = getDirection_Move (move);
      }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}

static Move_t 
getSymmetricalMoveRefXEq2 (Move_t move)
{

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = 4 - getStartX_Move (move);
  starty = getStartY_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
  switch (getDirection_Move (move))
    {
    case MOVE_DIR_T_PP:
      dir = MOVE_DIR_T_NP;
      break;
    case MOVE_DIR_T_P0:
      dir = MOVE_DIR_T_N0;
      break;
    case MOVE_DIR_T_PN:
      dir = MOVE_DIR_T_NN;
      break;
    case MOVE_DIR_T_NP:
      dir = MOVE_DIR_T_PP;
      break;
    case MOVE_DIR_T_N0:
      dir = MOVE_DIR_T_P0;
      break;
    case MOVE_DIR_T_NN:
      dir = MOVE_DIR_T_PN;
      break;
    default:
      dir = getDirection_Move (move);
    }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}

static Move_t 
getSymmetricalMoveRefXEqY (Move_t move)
{
  

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = getStartY_Move (move);
  starty = getStartX_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
  switch (getDirection_Move (move))
    {
    case MOVE_DIR_T_P0:
      dir = MOVE_DIR_T_0P;
      break;
    case MOVE_DIR_T_0P:
      dir = MOVE_DIR_T_P0;
      break;
    case MOVE_DIR_T_NP:
      dir = MOVE_DIR_T_PN;
      break;
    case MOVE_DIR_T_N0:
      dir = MOVE_DIR_T_0N;
      break;
    case MOVE_DIR_T_0N:
      dir = MOVE_DIR_T_N0;
      break;
    case MOVE_DIR_T_PN:
      dir = MOVE_DIR_T_NP;
      break;
    default:
      dir = getDirection_Move (move);
    }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}

static Move_t 
getSymmetricalMoveRefXEq4MnY (Move_t move) 
{

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = 4 - getStartY_Move (move);
  starty = 4 - getStartX_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
  switch (getDirection_Move (move))
    {
    case MOVE_DIR_T_P0:
      dir = MOVE_DIR_T_0N;
      break;
    case MOVE_DIR_T_PP:
      dir = MOVE_DIR_T_NN;
      break;
    case MOVE_DIR_T_0P:
      dir = MOVE_DIR_T_N0;
      break;
    case MOVE_DIR_T_N0:
      dir = MOVE_DIR_T_0P;
      break;
    case MOVE_DIR_T_NN:
      dir = MOVE_DIR_T_PP;
      break;
    case MOVE_DIR_T_0N:
      dir = MOVE_DIR_T_P0;
      break;
    default:
      dir = getDirection_Move (move);
    }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}

static Move_t 
getSymmetricalMoveRotClk (Move_t move) 
{

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = getStartY_Move (move);
  starty = 4 - getStartX_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
  switch (getDirection_Move (move))
    {
    case MOVE_DIR_T_P0:
      dir = MOVE_DIR_T_0N;
      break;
    case MOVE_DIR_T_PP:
      dir = MOVE_DIR_T_PN;
      break;
    case MOVE_DIR_T_0P:
      dir = MOVE_DIR_T_P0;
      break;
    case MOVE_DIR_T_NP:
      dir = MOVE_DIR_T_PP;
      break;
    case MOVE_DIR_T_N0:
      dir = MOVE_DIR_T_0P;
      break;
    case MOVE_DIR_T_NN:
      dir = MOVE_DIR_T_NP;
      break;
    case MOVE_DIR_T_0N:
      dir = MOVE_DIR_T_N0;
      break;
    case MOVE_DIR_T_PN:
      dir = MOVE_DIR_T_NN;
      break;
    default:
      dir = getDirection_Move (move);
    }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}

static Move_t 
getSymmetricalMoveRotAntiClk (Move_t move) 
{

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = 4 - getStartY_Move (move);
  starty = getStartX_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
  switch (getDirection_Move (move))
    {
    case MOVE_DIR_T_P0:
      dir = MOVE_DIR_T_0P;
      break;
    case MOVE_DIR_T_PP:
      dir = MOVE_DIR_T_NP;
      break;
    case MOVE_DIR_T_0P:
      dir = MOVE_DIR_T_N0;
      break;
    case MOVE_DIR_T_NP:
      dir = MOVE_DIR_T_NN;
      break;
    case MOVE_DIR_T_N0:
      dir = MOVE_DIR_T_0N;
      break;
    case MOVE_DIR_T_NN:
      dir = MOVE_DIR_T_PN;
      break;
    case MOVE_DIR_T_0N:
      dir = MOVE_DIR_T_P0;
      break;
    case MOVE_DIR_T_PN:
      dir = MOVE_DIR_T_PP;
      break;
    default:
      dir = getDirection_Move (move);
    }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}

Move_t 
getSymmetricalMoveRotPI (Move_t move) 
{

  unsigned int startx;
  unsigned int starty;
  unsigned int dir;

  startx = 4 - getStartX_Move (move);
  starty = 4 - getStartY_Move (move);

  if (getType_Move (move) == MOVE_T_SHIKAAR_PLACED)
    dir = 0;
  else
  switch (getDirection_Move (move))
    {
    case MOVE_DIR_T_P0:
      dir = MOVE_DIR_T_N0;
      break;
    case MOVE_DIR_T_PP:
      dir = MOVE_DIR_T_NN;
      break;
    case MOVE_DIR_T_0P:
      dir = MOVE_DIR_T_0N;
      break;
    case MOVE_DIR_T_NP:
      dir = MOVE_DIR_T_PN;
      break;
    case MOVE_DIR_T_N0:
      dir = MOVE_DIR_T_P0;
      break;
    case MOVE_DIR_T_NN:
      dir = MOVE_DIR_T_PP;
      break;
    case MOVE_DIR_T_0N:
      dir = MOVE_DIR_T_0P;
      break;
    case MOVE_DIR_T_PN:
      dir = MOVE_DIR_T_NP;
      break;
    default:
      dir = getDirection_Move (move);
    }

  return create_Move 
    ( getType_Move (move),
      startx, starty, dir );

}
