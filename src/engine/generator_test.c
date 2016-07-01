/**
 * generator_test.c
 * jaH
 * 4 Nov 2002
 *
 * Tests the implementation in gneerator.c
 */

#include "generator.h"
#include "test_utility.h"
#include <stdio.h>
#include <stdlib.h>

void testCase1 (void);
void testCase2 (void);
void testCase3 (void);
void testCase4 (void);
void testCase5 (void);
void testCase6 (void);

int
main ()
{

  srand (27);
  printf ("Testing move generator.\n");
  testCase1 ();
  testCase2 ();
  testCase3 ();
  testCase4 ();
  testCase5 ();
  testCase6 ();
  printf ("End of tests.\n");

  return 0;
}

void 
testCase1 (void)
{

  Board_t b;
  pMoveList_t mList;
  int i;
  
  b = getEmptyBoard ();
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 3);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
  setNumberOfShikaarKilled_Board (&b, 3);
  setNumberOfShikaarLeft_Board (&b, 3);
  setTurn_Board (&b, TURN_T_SHIKAAR);

  mList = generateUniqueNextMoves (b);
  printf ("Moves of test case 1:\n");
  print_move_list (mList);
  printf ("5 random variations on the first move:\n");
  for (i = 0; i < 5; i++)
    print_move 
      ( randomizeMove(b, mList->move) );

  destroy_MoveList (&mList);
  printf ("End of test case 1.\n");

}

void 
testCase2 (void)
{

  Board_t b;
  pMoveList_t mList;
  int i;

  b = getEmptyBoard ();
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 0);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 1);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 4);
  setNumberOfShikaarKilled_Board (&b, 0);
  setNumberOfShikaarLeft_Board (&b, 14);

  setTurn_Board (&b, TURN_T_TIGER);

  mList = generateUniqueNextMoves (b);
  printf ("Moves of test case 2:\n");
  print_move_list (mList);
  printf ("5 random variations on the first move:\n");
  for (i = 0; i < 5; i++)
    print_move 
      ( randomizeMove(b, mList->move) );

  destroy_MoveList (&mList);
  printf ("End of test case 2.\n");

}

void 
testCase3 (void)
{

  Board_t b;
  pMoveList_t mList;
  int i;

  b = getEmptyBoard ();
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 4);
  setNumberOfShikaarKilled_Board (&b, 0);
  setNumberOfShikaarLeft_Board (&b, 20);

  setTurn_Board (&b, TURN_T_SHIKAAR);

  mList = generateUniqueNextMoves (b);
  printf ("Moves of test case 3:\n");
  print_move_list (mList);
  printf ("30 random variations on the first move:\n");
  for (i = 0; i < 30; i++)
    print_move 
      ( randomizeMove(b, mList->move) );
  printf ("30 random variations on the second move:\n");
  for (i = 0; i < 30; i++)
    print_move 
      ( randomizeMove(b, mList->pnext->move) );

  destroy_MoveList (&mList);
  printf ("End of test case 3.\n");

}

void 
testCase4 (void)
{

  Board_t b;
  pMoveList_t mList;

  b = getEmptyBoard ();
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
  setNumberOfShikaarKilled_Board (&b, 1);
  setNumberOfShikaarLeft_Board (&b, 0);


  setTurn_Board (&b, TURN_T_TIGER);

  mList = generateUniqueNextMoves (b);
  printf ("Moves of test case 4:\n");
  print_move_list (mList);

  destroy_MoveList (&mList);
  printf ("End of test case 4.\n");

}

void 
testCase5 (void)
{

  Board_t b;
  pMoveList_t mList;
  int i;

b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 4);
setNumberOfShikaarLeft_Board (&b, 0);

  setTurn_Board (&b, TURN_T_SHIKAAR);

  mList = generateUniqueNextMoves (b);
  printf ("Moves of test case 5:\n");
  print_move_list (mList);
  printf ("5 random variations on the first move:\n");
  for (i = 0; i < 5; i++)
    print_move 
      ( randomizeMove(b, mList->move) );

  destroy_MoveList (&mList);
  printf ("End of test case 5.\n");

}

void 
testCase6 (void)
{

  Board_t b;
  pMoveList_t mList;
  int i;

b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 3);
setNumberOfShikaarKilled_Board (&b, 3);
setNumberOfShikaarLeft_Board (&b, 1);

  setTurn_Board (&b, TURN_T_TIGER);

  mList = generateUniqueNextMoves (b);
  printf ("Moves of test case 6:\n");
  print_move_list (mList);
  printf ("5 random variations on the first move:\n");
  for (i = 0; i < 5; i++)
    print_move 
      ( randomizeMove(b, mList->move) );

  destroy_MoveList (&mList);
  printf ("End of test case 6.\n");

}
