/**
 * move_test.c
 * 14 Oct 2002
 * jah
 *
 * Tests the implementation in move.c
 *
 * Testing strategy:
 *
 * checking for invalid moves:
 *   check whether the following moves are correctly identified as
 *   invalid:
 *
 *  A. shikaar placed
 *   1. no shikaar left
 *   2. not empty
 *  B. shikaar moved
 *   1. skikaar still left
 *   2. starting position empty
 *   3. invalid direction (ending position not empty)
 *   4. invalid direction (ending position out of board)
 *   5. invalid direction (no diagonal)
 *  C. tiger normal
 *   1. starting position not tiger
 *   2. ending position not empty
 *   3. ending position out of board
 *  D. tiger take
 *   1. starting position not tiger
 *   2. ending position not empty
 *   3. ending position out of board
 *   4. middle position not shikaar
 *   5. direction without diagonal
 *
 * Each test will isolate conditions where all other conditions are
 * met, except the one being tested as far as possible. This keeps is
 * line with the sinlge point of failure theory, which states that
 * "failure are only rarely the result of sinultaneous failure of two
 * (or more) faults." [1]
 *
 * Along similar lines the following tests are carried out to verify that
 * the correct execution of the software for the tranformation part:
 *
 * A. shikaar placed 
 *  1. correct decrease in number of shikaar left
 *  2. other parameters remain constant.
 * (the boundaries are checked, one left, all left, 1 killed, all killed)
 *
 * B. shikaar moved
 *  1. parameters remain invariant
 * (a test case for each direction, and 4 kinds of borders, 2 kinds of
 *  inners) 
 * 
 * C. tiger normal
 *  1. parameters remain invariant
 * (a test case for each direction, and 4 kinds of borders, 2 kinds of
 *  inners)
 *
 * D. tiger take
 *  1. number of shikaar killed increases by 1
 * (a test case for each direction, and 4 kinds of borders, 2 kinds of
 *  inners)
 *
 *
 * References:
 * [1] Jorgensen, Paul C. Software Testing: A craftman's approach. 1995.
 * CRC Press.
 */


#include "move.h"
#include <stdio.h>

void  testBorderEast (void);
void  testBorderWest (void);
void  testBorderNorth (void);
void  testBorderSouth (void);

void testShikaarPlacedNotLeft () {

  Board_t b;
  Move_t m;

  printf ("Testing shikaar placed not left ...");
  

  b = getEmptyBoard ();
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 1, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 4);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 0);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 1);
  setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 3);
  setNumberOfShikaarKilled_Board (&b, 0);
  setNumberOfShikaarLeft_Board (&b, 0);

  m = create_Move (MOVE_T_SHIKAAR_PLACED, 4, 4, 0); 

  if (isValid_Move (b, m)) {
    printf ("[failed]\n");
    exit (-1);
  }
 
  printf ("[passed]\n");

}

void testShikaarPlacedNotEmpty () {

  Board_t b;
  Move_t m;

  printf ("Testing shikaar placed not empty ...");

  b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 0);
setNumberOfShikaarLeft_Board (&b, 14);

 m =  create_Move (MOVE_T_SHIKAAR_PLACED, 2, 1, 0);
 if (isValid_Move (b, m)) {
    printf ("[failed]\n");
    exit (-1);
 }
 
 printf ("[passed]\n");

}


void testShikaarPlaced () {
  testShikaarPlacedNotLeft ();
  testShikaarPlacedNotEmpty ();
}

void testShikaarMoved () {

  testBorderEast ();
  testBorderWest ();
  testBorderNorth ();
  testBorderSouth ();
  
}

void testInvalidity ()
{

  printf ("Testing invalid moves ...\n");

  testShikaarPlaced ();
  testShikaarMoved ();

  printf ("[passed]\n");

}


int main () {

  printf ("Testing move validation and tranformation of boards on moves...\n");
  testInvalidity ();
  //  testTransformations ();

  printf ("all tests passed...\n");

  return 0;
}

void  testBorderEast (void) {

  Board_t b;
  Move_t m;
  
b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 2);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 0);
setNumberOfShikaarLeft_Board (&b, 10);

 m = create_Move (MOVE_T_SHIKAAR_MOVED, 4, 2, MOVE_DIR_T_P0);

 if (isValid_Move (b, m)) {
    printf ("[failed]\n");
    exit (-1);
 }
 
 printf ("[passed]\n");
 
}

void  testBorderWest (void) {

  Board_t b;
  Move_t m;
  
b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 0);
setNumberOfShikaarLeft_Board (&b, 7);

 m = create_Move (MOVE_T_SHIKAAR_MOVED, 0, 2, MOVE_DIR_T_NP);

 if (isValid_Move (b, m)) {
    printf ("[failed]\n");
    exit (-1);
 }
 
 printf ("[passed]\n");

} 
void  testBorderNorth (void) {
   Board_t b;
  Move_t m;
  b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 0);
setNumberOfShikaarLeft_Board (&b, 7);


 m = create_Move (MOVE_T_SHIKAAR_MOVED, 2, 4, MOVE_DIR_T_PP);

 if (isValid_Move (b, m)) {
    printf ("[failed]\n");
    exit (-1);
 }
 
 printf ("[passed]\n");            
}

void  testBorderSouth (void) {
  Board_t b;
  Move_t m;
  b = getEmptyBoard ();
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 1);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 3);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 1);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 3);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 4);
setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 2);
setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 4, 4);
setNumberOfShikaarKilled_Board (&b, 0);
setNumberOfShikaarLeft_Board (&b, 5);


 m = create_Move (MOVE_T_SHIKAAR_MOVED, 2, 0, MOVE_DIR_T_NN);

 if (isValid_Move (b, m)) {
    printf ("[failed]\n");
    exit (-1);
 }
 
 printf ("[passed]\n");
}

