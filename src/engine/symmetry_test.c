/**
 * symmetry_test.c
 * 13 Oct 2002
 * jah and suraj
 *
 * Tests the functions defined in symmetry.h.
 */

#include "symmetry.h"
#include <stdio.h>

void checkYEq2 () {

  Board_t b1, b2;

  printf ("Checking Y = 2 ...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 17);
  setNumberOfShikaarLeft_Board (&b2, 17);
  setNumberOfShikaarKilled_Board (&b1, 1);
  setNumberOfShikaarKilled_Board (&b2, 1);
  setTurn_Board (&b1, TURN_T_SHIKAAR);
  setTurn_Board (&b2, TURN_T_SHIKAAR);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 0, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 2, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 4);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 3);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 1, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 3, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 2, 3);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 3);

  if (
      !checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      !isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

void checkXEq2 () {

  Board_t b1, b2;

  printf ("Checking X = 2 ...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 14);
  setNumberOfShikaarLeft_Board (&b2, 14);
  setNumberOfShikaarKilled_Board (&b1, 2);
  setNumberOfShikaarKilled_Board (&b2, 2);
  setTurn_Board (&b1, TURN_T_TIGER);
  setTurn_Board (&b2, TURN_T_TIGER);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 0, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 3);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 4);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 1, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 1, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 3, 3);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 2);

  if (
      checkReflectionYEq2_Symmetry (b1, b2) ||
      !checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      !isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

void checkXEqY () {

  Board_t b1, b2;

  printf ("Checking X = Y ...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 10);
  setNumberOfShikaarLeft_Board (&b2, 10);
  setNumberOfShikaarKilled_Board (&b1, 4);
  setNumberOfShikaarKilled_Board (&b2, 4);
  setTurn_Board (&b1, TURN_T_SHIKAAR);
  setTurn_Board (&b2, TURN_T_SHIKAAR);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 3);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 4);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 2, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 3, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 3, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 2, 3);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 3);

  if (
      checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      !checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      !isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

void checkXEq4MnY () {

  Board_t b1, b2;

  printf ("Checking X = 4 - Y ...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 7);
  setNumberOfShikaarLeft_Board (&b2, 7);
  setNumberOfShikaarKilled_Board (&b1, 5);
  setNumberOfShikaarKilled_Board (&b2, 5);
  setTurn_Board (&b1, TURN_T_TIGER);
  setTurn_Board (&b2, TURN_T_TIGER);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 3, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 0, 4);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 4);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 1, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 2, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 3);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 4);

  if (
      checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      !checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      !isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

void checkAntiClockwise () {

  Board_t b1, b2;

  printf ("Checking anti-clockwise rotation...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 5);
  setNumberOfShikaarLeft_Board (&b2, 5);
  setNumberOfShikaarKilled_Board (&b1, 5);
  setNumberOfShikaarKilled_Board (&b2, 5);
  setTurn_Board (&b1, TURN_T_SHIKAAR);
  setTurn_Board (&b2, TURN_T_SHIKAAR);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 2, 4);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 3);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 0, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 0, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 4);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 3);

  if (
      checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      !checkRotationAntiClockwise_Symmetry (b1, b2) ||
      !isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

void checkClockwise () {

  Board_t b1, b2;

  printf ("Checking clockwise rotation...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 0);
  setNumberOfShikaarLeft_Board (&b2, 0);
  setNumberOfShikaarKilled_Board (&b1, 7);
  setNumberOfShikaarKilled_Board (&b2, 7);
  setTurn_Board (&b1, TURN_T_TIGER);
  setTurn_Board (&b2, TURN_T_TIGER);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 2, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 4, 4);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 3);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 1, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 3, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 4);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 4);

  if (
      checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      !checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      !isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

void checkUnsymmetrical () {

  Board_t b1, b2;

  printf ("Checking unsymmetrical...");
  b1 = getEmptyBoard ();
  b2 = getEmptyBoard ();
  setNumberOfShikaarLeft_Board (&b1, 0);
  setNumberOfShikaarLeft_Board (&b2, 0);
  setNumberOfShikaarKilled_Board (&b1, 6);
  setNumberOfShikaarKilled_Board (&b2, 6);
  setTurn_Board (&b1, TURN_T_TIGER);
  setTurn_Board (&b2, TURN_T_TIGER);
  
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 0, 4);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 1, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 2, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_TIGER, 4, 4);
  
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 0, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 3, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 2);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 4, 3);
  setPieceAtPosition_Board (&b1, PIECE_T_SHIKAAR, 1, 1);

  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 1, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 3, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_TIGER, 4, 4);
  
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 0, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 1, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 3);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 2, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 0);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 1);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 2);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 3, 4);
  setPieceAtPosition_Board (&b2, PIECE_T_SHIKAAR, 4, 2);

  if (
      checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      isEquivalent_Symmetry (b1, b2) ||
      !isValid_Board (b1) ||
      !isValid_Board (b2)
      )
    {
      printf ("[failed]\n");
      exit (-1);
    }

  printf ("[passed]\n");

}

int main () {

  printf ("Checking symmetry functions...\n");
  
  checkYEq2 ();
  checkXEq2 ();
  checkXEqY ();
  checkXEq4MnY ();
  checkClockwise ();
  checkAntiClockwise ();
  checkUnsymmetrical ();

  printf ("All tests passed\n");

  return 0;

}
