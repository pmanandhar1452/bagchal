/**
 * Board_test.c
 * Author: jaH
 * Date: 4 Aug 2002
 *
 * This file systematically tests the functions defined in
 * Board.h (see Board.nw after weaving). We perform both 
 * specification based and implementation based tests. But the
 * focus is on specification based (black box) tests. The
 * implementation is in Board.c.
 *
 * Test Plan 1:
 *
 *    1. create empty board
 *    2. check all parameters of empty board
 *    3. check isValid
 *    4. set num shikaar left, num shikaar taken, and turn
 *    5. check whether this value has been remembered.
 *    6. set 4 tigers at the corners
 *    7. check isValid
 *    8. copy board
 *    9. randomly place shikaars and tigers in copied board, and random parameters
 *   10. check whether the old board retains the old configuration
 *   11. and new board the new config.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

int num_ShikaarKilled_set;
int num_ShikaarLeft_set;
int turn_set;


void checkEmptyBoard (Board_t b) {
  int x, y;
  printf ("Checking empty board ...\n");
  
  for (x = 0; x < 5; x++)
  for (y = 0; y < 5; y++)
    {
      if (getPieceAtPosition_Board (b, x, y) != PIECE_T_EMPTY) {
	printf ("failed!!\n");
	exit (-1);
      }
    }

  // check other params
  if ( getNumberOfShikaarKilled_Board (b) != 0 ||
       getNumberOfShikaarLeft_Board (b) != 0 ||
       getTurn_Board (b) != TURN_T_SHIKAAR 
       ) {
  	printf ("failed!!\n");
	exit (-1);
  }

  printf ("passed\n");

}

void checkIsValid (Board_t b, Boolean_t valid) {
  printf("Checking isValid () ...");
  if ( isValid_Board (b) != valid ) {
    printf ("[failed]\n");
    exit (-1);
  }
  printf ("[passed]\n");
}


void checkSetParameters (pBoard_t pb) {

  printf ("Checking set parameters ...\n");
  num_ShikaarKilled_set = (rand ()/(double)RAND_MAX)*26;
  num_ShikaarLeft_set = (rand()/(double)RAND_MAX)*26;
  turn_set = (rand()/(double)RAND_MAX)*2;

  setNumberOfShikaarLeft_Board (pb, num_ShikaarLeft_set);
  print_bits (*pb);
  printf ("\n");
  setNumberOfShikaarKilled_Board (pb, num_ShikaarKilled_set);
  print_bits (*pb);
  printf ("\n");
  setTurn_Board (pb, turn_set);
  print_bits (*pb);
  printf ("\n");


  printf ("Number of shikaar left = %d\n", num_ShikaarLeft_set);
  printf ("Number of shikaar killed = %d\n", num_ShikaarKilled_set);
  printf ("Turn = %d\n", turn_set);

}

void checkGetParameters (Board_t b) {

  printf ("Checking get parameters ...\n");

  printf ("Number of shikaar left = %d\n", getNumberOfShikaarLeft_Board(b));
  printf ("Number of shikaar killed = %d\n", getNumberOfShikaarKilled_Board(b));
  printf ("Turn = %d\n", getTurn_Board (b));

  if (
      num_ShikaarKilled_set != getNumberOfShikaarKilled_Board (b) ||
      num_ShikaarLeft_set != getNumberOfShikaarLeft_Board (b) ||
      turn_set != getTurn_Board (b)
      )
    {
      printf ("[Failed]\n");
      exit (-1);
    }

  printf ("[Passed]\n");


}

void check4Corners (pBoard_t pb) {

  printf ("Checking tigers at 4 corners ...\n");

  setPieceAtPosition_Board (pb, PIECE_T_TIGER, 0, 0);
  setPieceAtPosition_Board (pb, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (pb, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (pb, PIECE_T_TIGER, 4, 4);


  checkIsValid (*pb, TRUE);
 
}


int main () {

  Board_t b, b1;
  int i;

  Piece_t piece [7];
  int x[7];
  int y[7];

  srand (26723423);
  
  b = getEmptyBoard ();
  checkEmptyBoard (b);
  checkIsValid (b, FALSE);
  checkSetParameters (&b);
  checkGetParameters (b);
  check4Corners (&b);
  
  b1 = copyBoard (b);
  
  for (i = 0; i < 7; i++) {

    x[i] = (rand()/(float)RAND_MAX)*5;
    y[i] = (rand()/(float)RAND_MAX)*5;
    piece[i] = (rand()/(float)RAND_MAX)*3;
    
    setPieceAtPosition_Board (&b1, piece[i], x[i], y[i]);

  }

  printf ("Checking whether boards are equal ...:%d\n", isEqual_Board (b, b1));
  checkIsValid (b, TRUE);

  printf ("Checking other board random postions...\n");
  for (i = 0; i < 7; i++) {
    if ( getPieceAtPosition_Board (b1, x[i], y[i]) != piece[i] )
      {
	printf ("[failed]\n");
	exit (-1);
      }
  }

  printf ("All tests passed!!\n");

  return 0;
    
  
}


