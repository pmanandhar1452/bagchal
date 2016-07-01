/**
 * move.h
 * 13 Oct 2002
 * jah and suraj
 *
 * ============== Change Log ===============================
 *
 * jaH, 2 April 2003
 *
 * Added function isValid_Move_noCheckBoard
 *
 * =========================================================
 * 
 * A move describes a tranformation from a particular board to the next
 * board in a game of bagchal. Let us denote the begining board by B and
 * the board after a move is made by B'. If getTurn_Board (B) is TURN_T_SHIKAAR
 * getTurn_Board (B') has to be TURN_T_TIGER and vice versa. A move has to
 * be taken with respect to a board, otherwise it is quite meaning-less. A move
 * is valid or invalid with respect to a board. We will not, however store
 * the board with respect to the move. So, the same move can mean quite different
 * things when taken with respect to different boards and a valid move for
 * one board might be invalid for another board.
 */

#ifndef bagchal_engine_move_h
#define bagchal_engine_move_h

#include "Board.h"

/**
 * The Move_t data-type represents a move as descibed above.
 * The move is represented as a starting position and an optional
 * direction.
 */
typedef struct move_t_tag {

  // lsb_bit:
  // move_type == 0 SHIKAAR's move
  // move_type == 1 TIGER's move
  //
  // msb_bit:
  // for lsb_bit == 0 (SHIKAAR's move)
  //   0 == a new piece is placed on the board 
  //        getNumberOfShikaarLeft_Board (B) = 
  //        getNumberOfShikaarLeft_Board (B') + 1
  //   1 == a piece already on the board is moved to a different position
  //        getNumberOfShikaarLeft_Board (B) = 0
  //   
  // for lsb_bit == 1 (TIGER's move)
  //   0 == a non-taking move
  //        getNumberOfShikaarKilled (B) = getNumberOfShikaarKilled (B')
  //   1 == a taking move
  //        getNUmberOfShikaarKilled (B) = getNumberOfShikaarKilled (B') - 1
  unsigned int move_type: 2;

  // staring position
  unsigned int x: 3;
  unsigned int y: 3;

  // this field is not defined for
  // move_type = 00
  //
  //   0 - +ve delX 0 delY
  //   1 - +ve delX +ve delY
  //   2 - 0 delX +ve delY
  //   3 - -ve delX +ve delY
  //   4 - -ve delX 0 delY
  //   5 - -ve delX -ve delY
  //   6 - 0 delX -ve delY
  //   7 - +ve delX -ve delY
  unsigned int dir: 3;

} Move_t;

typedef Move_t * pMove_t;

#define MOVE_T_SHIKAAR_PLACED 0
#define MOVE_T_SHIKAAR_MOVED  2
#define MOVE_T_TIGER_NORMAL   1
#define MOVE_T_TIGER_TAKE     3

#define MOVE_DIR_T_P0 0
#define MOVE_DIR_T_PP 1
#define MOVE_DIR_T_0P 2
#define MOVE_DIR_T_NP 3
#define MOVE_DIR_T_N0 4
#define MOVE_DIR_T_NN 5
#define MOVE_DIR_T_0N 6
#define MOVE_DIR_T_PN 7

/**
 * Checks whether the given move is valid for the given board.
 */
Boolean_t isValid_Move (Board_t, Move_t);

/**
 * Checks whether the given tiger_normal or tiger_take move is
 * valid, without checking the validity of the board.
 */
Boolean_t isValid_Move_noCheckBoard (Board_t, Move_t);

/**
 * Returns the transformed board after a move is made on the
 * given board. If the given move is not valid for the given
 * board the operation fails.
 */
Board_t transform_Move (Board_t, Move_t);

/**
 * Create a move with given specifications.
 *   type == one of MOVE_T_*
 *   direction == one of MOVE_DIR_T_*
 */
Move_t 
create_Move (
	     unsigned int type, 
	     unsigned int startx,
	     unsigned int starty,
	     unsigned int direction
	     );

/**
 * Returns the move type.
 */
unsigned int getType_Move (Move_t);

/**
 * Returns the starting position x
 */
unsigned int getStartX_Move (Move_t);

/**
 * Returns the starting positon y
 */
unsigned int getStartY_Move (Move_t);

/**
 * Returns the direction.
 */
unsigned int getDirection_Move (Move_t);

Move_t copy_Move (Move_t);

/**
 * checks whether two moves are identical.
 */
Boolean_t equals_Move (Move_t, Move_t);		    

/**
 * returns the final co-ordinates of a piece after a move.
 */
int getFinalX_Move (Move_t);
int getFinalY_Move (Move_t);

#endif
