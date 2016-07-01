/**
 * evaluation_test.c
 * jaH
 * 5 Nov 2002
 *
 * Tests the evaluation function in evaluation.h
 *
 */

#include "evaluation.h"
#include <stdio.h>

void testCase1 ();
void testCase2 ();
void testCase3 ();
void testCase4 ();
void testCase5 ();
void testCase6 ();

int
main ()
{

  printf ("Testing evaluation function.\n");

  testCase1 ();
  testCase2 ();
  testCase3 ();
  testCase4 ();
  testCase5 ();

  printf ("End of evaluation test.\n");

  return 0;

}

void
testCase1 ()
{

  Board_t b;

b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 4);
setNumberOfShikaarKilled_Board (&b, 0);
setNumberOfShikaarLeft_Board (&b, 14);

  setTurn_Board (&b, TURN_T_TIGER);
  printf ("Evauation for test case 1: %d\n", 
          evaluate_Static (b));

}

void
testCase2 ()
{

  Board_t b;

b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 4);
setNumberOfShikaarLeft_Board (&b, 2);

  setTurn_Board ( &b, TURN_T_SHIKAAR );

  printf ("Evauation for test case 2: %d\n", 
          evaluate_Static (b));

}


void
testCase3 ()
{

  Board_t b;
b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 1);
setNumberOfShikaarLeft_Board (&b, 0);
  setTurn_Board ( &b, TURN_T_SHIKAAR );

  printf ("Evauation for test case 3: %d\n", 
          evaluate_Static (b));

}


void
testCase4 ()
{

  Board_t b;

b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 5);
setNumberOfShikaarLeft_Board (&b, 0);

  setTurn_Board ( &b, TURN_T_TIGER );
  printf ("Evauation for test case 4: %d\n", 
          evaluate_Static (b));

}

void
testCase5 ()
{

  Board_t b;


b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 8);
setNumberOfShikaarLeft_Board (&b, 0);

  setTurn_Board ( &b, TURN_T_SHIKAAR );
  printf ("Evauation for test case 5: %d\n", 
          evaluate_Static (b));

}
