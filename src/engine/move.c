/**
 * move.c
 * 13 Oct 2002
 * jah and suraj
 *
 * ================== Change Log ============================
 *
 * jaH, 2 April 2003.
 *
 * Added implementation for isValid_Move_noCheckBoard
 * 
 * ==========================================================
 * 
 * Implementation for move.h.
 */

#include "move.h"

static Boolean_t 
checkValidDir (
	       unsigned int startx,
	       unsigned int starty,
	       unsigned int dir
	       )
{

  if (startx == 0) {
    if (
	dir == MOVE_DIR_T_NP ||
	dir == MOVE_DIR_T_N0 ||
	dir == MOVE_DIR_T_NN
	)
      return FALSE;
  }

  if (startx == 4) {
    if (
	dir == MOVE_DIR_T_PP ||
	dir == MOVE_DIR_T_P0 ||
	dir == MOVE_DIR_T_PN
	)
      return FALSE;
  }

  if (starty == 0) {
    if (
	dir == MOVE_DIR_T_PN ||
	dir == MOVE_DIR_T_0N ||
	dir == MOVE_DIR_T_NN
	)
      return FALSE;
  }

  if (starty == 4) {
    if (
	dir == MOVE_DIR_T_NP ||
	dir == MOVE_DIR_T_0P ||
	dir == MOVE_DIR_T_PP
	)
      return FALSE;
  }

  if ( 
      (
       (startx + starty) 
       % 2
       ) == 0
      ) 
    return TRUE;

  if (
      dir == MOVE_DIR_T_P0 ||
      dir == MOVE_DIR_T_N0 ||
      dir == MOVE_DIR_T_0N ||
      dir == MOVE_DIR_T_0P 
      )
    return TRUE;

  return FALSE;

}

static Boolean_t 
checkValidDir2Steps (
	       unsigned int startx,
	       unsigned int starty,
	       unsigned int dir
	       )
{

  if (startx == 0 || startx == 1) {
    if (
	dir == MOVE_DIR_T_NP ||
	dir == MOVE_DIR_T_N0 ||
	dir == MOVE_DIR_T_NN
	)
      return FALSE;
  }

  if (startx == 4 || startx == 3) {
    if (
	dir == MOVE_DIR_T_PP ||
	dir == MOVE_DIR_T_P0 ||
	dir == MOVE_DIR_T_PN
	)
      return FALSE;
  }

  if (starty == 0 || starty == 1) {
    if (
	dir == MOVE_DIR_T_PN ||
	dir == MOVE_DIR_T_0N ||
	dir == MOVE_DIR_T_NN
	)
      return FALSE;
  }

  if (starty == 4 || starty == 3) {
    if (
	dir == MOVE_DIR_T_NP ||
	dir == MOVE_DIR_T_0P ||
	dir == MOVE_DIR_T_PP
	)
      return FALSE;
  }

  if ( 
      (
       (startx + starty) 
       % 2
       ) == 0
      ) 
    return TRUE;

  if (
      dir == MOVE_DIR_T_P0 ||
      dir == MOVE_DIR_T_N0 ||
      dir == MOVE_DIR_T_0N ||
      dir == MOVE_DIR_T_0P 
      )
    return TRUE;

  return FALSE;

}

static unsigned int 
getFinalX (Move_t m, unsigned int step)
{
  int x;
  unsigned int dir = getDirection_Move (m);

  switch (dir) {
  case MOVE_DIR_T_P0:
  case MOVE_DIR_T_PN:
  case MOVE_DIR_T_PP:
    x = getStartX_Move (m) + step;
    break;
  case MOVE_DIR_T_N0:
  case MOVE_DIR_T_NN:
  case MOVE_DIR_T_NP:
    x = getStartX_Move (m) - step;
    break;
  case MOVE_DIR_T_0N:
  case MOVE_DIR_T_0P:
    x = getStartX_Move (m);
    break;
  }
#ifdef DEBUG_LEVEL_1
  assert (x >=0 && x <= 4);
#endif
  return x;

}

static unsigned int 
getFinalY (Move_t m, unsigned int step)
{
  int y;
  unsigned int dir = getDirection_Move (m);

  switch (dir) {
  case MOVE_DIR_T_0P:
  case MOVE_DIR_T_NP:
  case MOVE_DIR_T_PP:
    y = getStartY_Move (m) + step;
    break;
  case MOVE_DIR_T_0N:
  case MOVE_DIR_T_NN:
  case MOVE_DIR_T_PN:
    y = getStartY_Move (m) - step;
    break;
  case MOVE_DIR_T_N0:
  case MOVE_DIR_T_P0:
    y = getStartY_Move (m);
    break;
  }
#ifdef DEBUG_LEVEL_1
  assert (y >=0 && y <= 4);
#endif
  return y;

}

static
Boolean_t checkShikaarPlaced (Board_t b, Move_t m) {

  return ( getNumberOfShikaarLeft_Board (b) > 0 
	   &&
	   getPieceAtPosition_Board (
			      b, 
			      getStartX_Move (m),
			      getStartY_Move (m)
			      ) 
	          == PIECE_T_EMPTY
	   );
  
}

static Boolean_t
checkShikaarMoved (Board_t b, Move_t m)
{
  unsigned int fx, fy;

  // check that the number of shikaar left = 0
  if (
      getNumberOfShikaarLeft_Board (b) > 0
      )
    return FALSE;

  // check that starting position has shikaar
  if (
      getPieceAtPosition_Board (
				b, 
				getStartX_Move (m),
				getStartY_Move (m)
				)
         != PIECE_T_SHIKAAR
      )
    return FALSE;

  // check the direction is valid (1 step)
  if ( !checkValidDir (
		       getStartX_Move (m), 
		       getStartY_Move (m),
		       getDirection_Move (m)
		       )
       )
    return FALSE;

  // check that the final position is empty
  fx = getFinalX (m, 1);
  fy = getFinalY (m, 1);

  return (
      getPieceAtPosition_Board (b, fx, fy)
         == PIECE_T_EMPTY
      );
}

static Boolean_t 
checkTigerNormal (Board_t b, Move_t m)
{
  unsigned int fx, fy;

  // check that starting position has tiger
  if (
      getPieceAtPosition_Board (
				b, 
				getStartX_Move (m),
				getStartY_Move (m)
				)
         != PIECE_T_TIGER
      )
    return FALSE;

  // check the direction is valid
  if ( !checkValidDir (
		       getStartX_Move (m), 
		       getStartY_Move (m),
		       getDirection_Move (m)
		       )
       )
    return FALSE;

  // check that the final position is empty
  fx = getFinalX (m, 1);
  fy = getFinalY (m, 1);

  return (
      getPieceAtPosition_Board (b, fx, fy)
         == PIECE_T_EMPTY
      );
  
}

static Boolean_t 
checkTigerTake (Board_t b, Move_t m)
{
  unsigned int fx2, fy2;
  unsigned int fx1, fy1;

  // check that starting position has tiger
  if (
      getPieceAtPosition_Board (
				b, 
				getStartX_Move (m),
				getStartY_Move (m)
				)
         != PIECE_T_TIGER
      )
    return FALSE;

  // check the direction is valid (2 steps)
  if ( !checkValidDir2Steps (
		       getStartX_Move (m), 
		       getStartY_Move (m),
		       getDirection_Move (m)
		       )
       )
    return FALSE;

  // check that the final position is empty
  fx2 = getFinalX (m, 2);
  fy2 = getFinalY (m, 2);

  if (
      getPieceAtPosition_Board (b, fx2, fy2)
         != PIECE_T_EMPTY
      )
    return FALSE;

  // check that the middle position is shikaar
  fx1 = getFinalX (m, 1);
  fy1 = getFinalY (m, 1);

  return (
      getPieceAtPosition_Board (b, fx1, fy1)
         == PIECE_T_SHIKAAR
      );
}


/**
 * Checks whether the given move is valid for the given baord.
 */
Boolean_t isValid_Move (Board_t b, Move_t m) {

#ifdef DEBUG_LEVEL_1
  assert ( isValid_Board (b) );
#endif

  // check whether turn is correct.
  switch ( getTurn_Board (b) ) {
  case TURN_T_SHIKAAR:
    if ( !
	 (
	  getType_Move (m) == MOVE_T_SHIKAAR_PLACED ||
	  getType_Move (m) == MOVE_T_SHIKAAR_MOVED
	  )
	 )
      return FALSE;
    break;
  case TURN_T_TIGER:
    if ( !
	 (
	  getType_Move (m) == MOVE_T_TIGER_NORMAL ||
	  getType_Move (m) == MOVE_T_TIGER_TAKE
	  )
	 )
      return FALSE;
    break;

#ifdef DEBUG_LEVEL_1
  default:
    assert (0);
#endif
  } // switch

  switch (getType_Move (m)) {
  case MOVE_T_SHIKAAR_PLACED:
    if (!checkShikaarPlaced (b, m)) 
      return FALSE;
    break;

  case MOVE_T_SHIKAAR_MOVED:
    if (!checkShikaarMoved (b, m)) 
      return FALSE;
    break;

  case MOVE_T_TIGER_NORMAL:
    if (!checkTigerNormal (b, m)) 
      return FALSE;
    break;

  case MOVE_T_TIGER_TAKE:
    if (!checkTigerTake (b, m)) 
      return FALSE;
    break;

#ifdef DEBUG_LEVEL_1
  default:
    assert (0);
#endif
  }

  return TRUE;

}
/*
 * Checks whether the given move is valid for the given board, but
 * only checks tiger moves and goes not check validity of board.
 * Used to check accessibility.
 * 
 */
Boolean_t isValid_Move_noCheckBoard (Board_t b, Move_t m) {

  switch (getType_Move (m)) {

  case MOVE_T_TIGER_NORMAL:
    return checkTigerNormal (b, m);

  case MOVE_T_TIGER_TAKE:
    return checkTigerTake (b, m);

  }

  return FALSE;

}


Board_t makeMoveShikaarPlaced (Board_t b, Move_t m)
{

  Board_t nb;
  nb = copyBoard (b);
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_SHIKAAR,
			    getStartX_Move (m),
			    getStartY_Move (m)
			    );
  setNumberOfShikaarLeft_Board (
				&nb,
				getNumberOfShikaarLeft_Board (b) - 1
				);
  return nb;

}

Board_t makeMoveShikaarMoved (Board_t b, Move_t m)
{

  Board_t nb;
  unsigned int fx, fy;
  fx = getFinalX (m, 1);
  fy = getFinalY (m, 1);

  nb = copyBoard (b);
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_SHIKAAR,
			    fx,
			    fy
			    );
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_EMPTY,
			    getStartX_Move (m),
			    getStartY_Move (m)
			    );

  return nb;

}

Board_t makeMoveShikaar (Board_t b, Move_t m)
{
  Board_t new_board;
  switch ( getType_Move (m) ) {
  case MOVE_T_SHIKAAR_PLACED:
    new_board = makeMoveShikaarPlaced (b, m);
    break;
  case MOVE_T_SHIKAAR_MOVED:
    new_board = makeMoveShikaarMoved (b, m);
    break;
  
#ifdef DEBUG_LEVEL_1
  default:
    assert (0);
#endif
  } // switch
  
  setTurn_Board (&new_board, TURN_T_TIGER);
  return new_board; 

}

Board_t makeMoveTigerNormal (Board_t b, Move_t m)
{

  Board_t nb;
  unsigned int fx, fy;
  fx = getFinalX (m, 1);
  fy = getFinalY (m, 1);

  nb = copyBoard (b);
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_TIGER,
			    fx,
			    fy
			    );
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_EMPTY,
			    getStartX_Move (m),
			    getStartY_Move (m)
			    );

  return nb;

}

Board_t makeMoveTigerTake (Board_t b, Move_t m)
{

  Board_t nb;
  unsigned int fx2, fy2;
  unsigned int fx1, fy1;
  fx1 = getFinalX (m, 1);
  fy1 = getFinalY (m, 1);
  fx2 = getFinalX (m, 2);
  fy2 = getFinalY (m, 2);

  nb = copyBoard (b);
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_TIGER,
			    fx2,
			    fy2
			    );
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_EMPTY,
			    fx1,
			    fy1
			    );
  setPieceAtPosition_Board (
			    &nb, 
			    PIECE_T_EMPTY,
			    getStartX_Move (m),
			    getStartY_Move (m)
			    );

  setNumberOfShikaarKilled_Board (
				  &nb,
				  getNumberOfShikaarKilled_Board (b) + 1
				  );

  return nb;

}

Board_t makeMoveTiger (Board_t b, Move_t m)
{
  Board_t new_board;
  
  switch ( getType_Move (m) ) {
  case MOVE_T_TIGER_NORMAL:
    new_board = makeMoveTigerNormal (b, m);
    break;
  case MOVE_T_TIGER_TAKE:
    new_board = makeMoveTigerTake (b, m);
    break;
  
#ifdef DEBUG_LEVEL_1
  default:
    assert (0);
#endif
  } // switch

  setTurn_Board (&new_board, TURN_T_SHIKAAR);
  return new_board;

}


/**
 * Returns the transformed board after a move is made on the
 * given board. If the given move is not valid for the given
 * board the operation fails.
 */
Board_t transform_Move (Board_t b, Move_t m) {

#ifdef DEBUG_LEVEL_1
  assert ( isValid_Move (b, m) );
#endif

  // check whether turn is correct.
  switch ( getTurn_Board (b) ) {
  case TURN_T_SHIKAAR:
    return makeMoveShikaar (b, m);

  case TURN_T_TIGER:
    return makeMoveTiger (b, m);


#ifdef DEBUG_LEVEL_1
  default:
    assert (0);
#endif
  } // switch

  return 0;

}

/**
 * Create a move with given specifications.
 *   type == one of MOVE_T_*
 *   direction == one of DIR_T_*
 */
Move_t 
create_Move (
	     unsigned int type, 
	     unsigned int startx,
	     unsigned int starty,
	     unsigned int direction
	     ) 
{
  Move_t m;

#ifdef DEBUG_LEVEL_1
  assert ( 
	  type >= 0 && type <= 1 && 
	  startx >= 0 && startx <= 4 &&
	  starty >= 0 && starty <= 4 &&
	  direction >= 0 && direction <= 7
	  );
#endif

  m.move_type = type;
  m.x = startx;
  m.y = starty;
  if (type == MOVE_T_SHIKAAR_PLACED)
    m.dir = 0;
  else
    m.dir = direction;

  return m;

}

Move_t copy_Move (Move_t m) {
  return m;
}

/**
 * Returns the move type.
 */
unsigned int getType_Move (Move_t m) {
  return m.move_type;
}

/**
 * Returns the starting position x
 */
unsigned int getStartX_Move (Move_t m) {
  return m.x;
}

/**
 * Returns the starting positon y
 */
unsigned int getStartY_Move (Move_t m) {
  return m.y;
}

/**
 * Returns the direction.
 */
unsigned int getDirection_Move (Move_t m) {
#ifdef DEBUG_LEVEL_1
  assert ( m.move_type != 0 );
#endif
  return m.dir;
}

Boolean_t
equals_Move (Move_t m1, Move_t m2) {

  return (
          (m1.move_type == m2.move_type) &&
          (m1.x == m2.x) &&
          (m1.y == m2.y) &&
          (m1.dir == m2.dir)
          );

}

int getFinalX_Move (Move_t m)
{
	switch (m.move_type) {
	case MOVE_T_SHIKAAR_PLACED: 
		return m.x;
	case MOVE_T_SHIKAAR_MOVED:
	case MOVE_T_TIGER_NORMAL:
		return getFinalX (m, 1);
	case MOVE_T_TIGER_TAKE:
		return getFinalX (m, 2);
	}
	return 0;
}

int getFinalY_Move (Move_t m)
{
	switch (m.move_type) {
	case MOVE_T_SHIKAAR_PLACED: 
		return m.y;
	case MOVE_T_SHIKAAR_MOVED:
	case MOVE_T_TIGER_NORMAL:
		return getFinalY (m, 1);
	case MOVE_T_TIGER_TAKE:
		return getFinalY (m, 2);
	}
	return 0;
}
