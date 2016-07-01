/**
 * search_test.c
 * jaH, March 2003
 *
 * Tests the search implementation in search.c
 */

#include <stdio.h>
#include "search.h"
#include "test_utility.h"

#define TEST_DEPTH 5

void testInitialPosition ();
void testOneInaccesible ();

int main ()
{
	testInitialPosition ();
	testOneInaccesible ();
	return 0;
}

void testInitialPosition ()
{
	printf ("Testing Search for initial position ...\n");
	Board_t b = getEmptyBoard ();
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 4);
	setNumberOfShikaarKilled_Board (&b, 0);
	setNumberOfShikaarLeft_Board (&b, 20);
	setTurn_Board (&b, TURN_T_SHIKAAR);
	Move_t move;
	int val = search (b, TEST_DEPTH, &move);
	printf ("Score: %d\n", val);
	printf ("Best Move: ");
	print_move (move);
	printf ("\n");
}

void testOneInaccesible ()
{
	printf ("Testing Search for pos 1 (one inaccesible) ...\n");
	Board_t b = getEmptyBoard ();
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 1);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 2);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 3);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 0, 4);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 2);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 1, 3);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 2, 4);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 0);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 3, 3);
	setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, 3, 4);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 1);
	setNumberOfShikaarKilled_Board (&b, 0);
	setNumberOfShikaarLeft_Board (&b, 12);
	setTurn_Board (&b, TURN_T_TIGER);
	Move_t move;
	int val = search (b, TEST_DEPTH, &move);
	printf ("Score: %d\n", val);
	printf ("Best Move: ");
	print_move (move);
	printf ("\n");

}
