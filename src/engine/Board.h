/**
* Board.h
*
* This file was supposed to be tangled from Board.nw, but
* due to a mistake, the more recent verion of Board.nw was
* deleted, and we would suugest the reader to refer to Board.nw
* for an introduction and then continue with this file.
*/

  #ifndef bagchal_engine_board_h
  #define bagchal_engine_board_h

  
  #include "types.h"


  
  typedef i64_t Board_t;     // the 64 bit bit-board
  typedef Board_t* pBoard_t; // pointer to Board_t


  typedef i2_t Piece_t;
  typedef Piece_t* pPiece_t;

  #define PIECE_T_EMPTY 0
  #define PIECE_T_TIGER 1
  #define PIECE_T_SHIKAAR 2
  #define PIECE_T_UNDEFINED 3


  typedef i1_t Turn_t;
  typedef Turn_t* pTurn_t;

  #define TURN_T_TIGER 1
  #define TURN_T_SHIKAAR 0


  
  /**
   * Returns the piece at position (x, y) x,y = {0, 1, 2, 3, 4}.
   */
  Piece_t getPieceAtPosition_Board (Board_t b, int x, int y);

  /**
   * Sets the piece at position (x, y) x,y = {0, 1, 2, 3, 4}.
   */
  void setPieceAtPosition_Board (pBoard_t b, Piece_t p, int x, int y);
  
  
  /**
   * Returns the number of shikaar already killed.
   */
  int getNumberOfShikaarKilled_Board (Board_t b);

  /**
   * sets the number of shikaar already killed.
   */
  void setNumberOfShikaarKilled_Board (pBoard_t b, int num);
  
  /**
   * Returns the number of shikaar left to be played.
   */
  int getNumberOfShikaarLeft_Board (Board_t b);

  /**
   * Sets the number of shikaar left to be played.
   */
  void setNumberOfShikaarLeft_Board (pBoard_t b, int num);

  /**
   * Returns the turn.
   */
  Turn_t getTurn_Board (Board_t b);
  
  /**
   * Set the turn.
   */
  void setTurn_Board (pBoard_t b, Turn_t t);

  /**
   * Returns TRUE when the board is valid, otherwise FALSE (these
   * types are defined in types.h.
   * This checks that there are no undefined values; that the
   * sum of the number of shikaar on the board, left to be played,
   * and killed is less than or equal to 21; and that there are
   * 4 and only 4 tigers on the board.
   */
  Boolean_t isValid_Board (Board_t b);

/*
  Returns whether two boards are equal without cosidering symmetry.
*/
Boolean_t isEqual_Board (Board_t, Board_t);

  /**
  * Returns a board with no peices, turn shikaar, 
  * numberofshikaar left and killed == 0.
  */
  Board_t getEmptyBoard ();

  /**
  * Copies a board.
  */
  Board_t copyBoard ( Board_t );

  #endif


