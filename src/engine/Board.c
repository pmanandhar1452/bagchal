/**
 * This file is the implementation of functions defined in
 * board.h
 *
 * date: 27 july 2002
 * authors: jaH and suraj
 */

#include "Board.h"
#include "utility.h"

// for debugging friendliness
#include "debug.h"
#include <assert.h>

// no domain checking
static Piece_t
getPieceAtPosition_Board_raw (
		Board_t b,
		int x, int y )
{
    Piece_t result;
    unsigned char bit_pos1;
    
    // do some clever bit manipulations
    // this part is dependent upon the internal bit
    // representations. Beware.
	
	bit_pos1 = 2*x + 10*y;
	result = b >> bit_pos1;
        result = result & 0x3;

	return result;	
}	

static int
getNumberOfShikaarKilled_Board_raw ( Board_t b )
{
  return (b >> (i64_t)50UL) & 0x1F;
}

static int
getNumberOfShikaarLeft_Board_raw ( Board_t b )
{
  return (b >> (i64_t)55UL) & 0x1F;
}

Piece_t 
getPieceAtPosition_Board (
		Board_t b,
		int x,
		int y )
{
	// check validity of domain
    #ifdef DEBUG_LEVEL_1
	assert ( x >= 0 && x < 5 && y >= 0 && y < 5 );
    #endif
	return getPieceAtPosition_Board_raw ( b, x, y );
		
}

int
getNumberOfShikaarKilled_Board ( Board_t b )
{
	return getNumberOfShikaarKilled_Board_raw (b); 
}

int
getNumberOfShikaarLeft_Board ( Board_t b )
{
	return getNumberOfShikaarLeft_Board_raw (b);
}
	
Turn_t
getTurn_Board ( Board_t b )
{
	return (b >> (i64_t)60UL) & 0x1;
}	

Boolean_t
isValid_Board ( Board_t b )
{
	int cnt_shikaar_left,
	    cnt_shikaar_killed,
    	    cnt_shikaar_onboard = 0,
	    cnt_tiger_onboard = 0;	    
	
	Piece_t p_at_pos;

	int x, y;

	for ( x = 0; x < 5; x++ )
	for ( y = 0; y < 5; y++ )
	{
		p_at_pos = getPieceAtPosition_Board_raw ( b, x, y );
		switch ( p_at_pos ) {
		case PIECE_T_UNDEFINED:
			return FALSE;
		case PIECE_T_SHIKAAR:
			cnt_shikaar_onboard++;
			break;
		case PIECE_T_TIGER:
			cnt_tiger_onboard++;
		}
	}

	if ( cnt_tiger_onboard != 4 ) return FALSE;
	
	cnt_shikaar_killed = getNumberOfShikaarKilled_Board_raw ( b );
	cnt_shikaar_left = getNumberOfShikaarLeft_Board_raw ( b );

	if ( (
		cnt_shikaar_killed +
		cnt_shikaar_left +
		cnt_shikaar_onboard
		) > 21
			)
		return FALSE;
	
	return TRUE;	
				
}


/**
 * Sets the piece at position (x, y) x,y = {0, 1, 2, 3, 4}.
 */
void setPieceAtPosition_Board (pBoard_t b, Piece_t p, int x, int y) {
  int bit_pos1;
  Board_t new_board;
  i64_t position_mask;

  bit_pos1 = 2*x + 10*y;
  position_mask = generateMask_i64_t (bit_pos1);
  position_mask |= generateMask_i64_t (bit_pos1 + 1);

  (*b) = (*b) & (~position_mask);
  new_board = (i64_t)(p)<<bit_pos1;
  (*b) = (*b) | new_board;
 
}
  
/**
 * sets the number of shikaar already killed.
 */
void setNumberOfShikaarKilled_Board (pBoard_t b, int num) {
  i64_t position_mask;
  Board_t new_board;
  
  num &= 0x1F;

  position_mask = generateMask_i64_t (50);
  position_mask |= generateMask_i64_t (51);
  position_mask |= generateMask_i64_t (52);
  position_mask |= generateMask_i64_t (53);
  position_mask |= generateMask_i64_t (54);
  
  (*b) = (*b) & (~position_mask);
  new_board = (i64_t)(num)<<50;
  (*b) = (*b) | new_board;

}

/**
 * Sets the number of shikaar left to be played.
 */
void setNumberOfShikaarLeft_Board (pBoard_t b, int num) {

  i64_t position_mask;
  Board_t new_board;

  num &= 0x1F;

  position_mask = generateMask_i64_t (55);
  position_mask |= generateMask_i64_t (56);
  position_mask |= generateMask_i64_t (57);
  position_mask |= generateMask_i64_t (58);
  position_mask |= generateMask_i64_t (59);

  (*b) = (*b) & (~position_mask);
  new_board = (i64_t)(num)<<55;
  (*b) = (*b) | new_board;

}

/**
 * Set the turn.
 */
void setTurn_Board (pBoard_t b, Turn_t t) {

  i64_t position_mask;
  Board_t new_board;

  t &= 0x1;

  position_mask = generateMask_i64_t (60);
  
  (*b) = (*b) & (~position_mask);
  new_board = (i64_t)(t)<<60;
  (*b) = (*b) | new_board;

}

/**
 * Returns a board with no peices, turn shikaar, 
 * numberofshikaar left and killed == 0.
 */
Board_t getEmptyBoard () {
  return 0;
}

/**
 * Copies a board.
 */
Board_t copyBoard ( Board_t b) {
  return b;
}


/*
  Returns whether two boards are equal without cosidering symmetry.
*/
Boolean_t isEqual_Board (Board_t b1, Board_t b2) {
  return (b1 == b2);
}
