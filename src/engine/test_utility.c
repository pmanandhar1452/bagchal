/**
 * test_utility.c
 * jaH
 * 4 Nov 2002
 *
 * implementation of test_utility.h
 */

#include "test_utility.h"
#include <stdlib.h>
#include <stdio.h>

Board_t getInitialBoard ()
{
	Board_t b = getEmptyBoard ();
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 0);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 0, 4);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 0);
	setPieceAtPosition_Board (&b, PIECE_T_TIGER, 4, 4);
	setNumberOfShikaarKilled_Board (&b, 0);
	setNumberOfShikaarLeft_Board (&b, 20);
	setTurn_Board (&b, TURN_T_SHIKAAR);
	return b;
}

void print_board (Board_t b)
{
	printf ("Number of Shikaar killed, left = %d, %di\n",
			getNumberOfShikaarKilled_Board (b),
			getNumberOfShikaarLeft_Board (b));
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			Piece_t p = getPieceAtPosition_Board (b, i, j);
			switch (p) {
			case PIECE_T_EMPTY: 
				printf ("*");
				break;
			case PIECE_T_TIGER:
				printf ("T");
				break;
			case PIECE_T_SHIKAAR:
				printf ("S");
				break;
			default:
				printf ("U");
				break;
			}
		}	    	
		printf ("\n");
	}
}

void print_move ( Move_t move ) {

  printf ("<move type=\"%d\" x=\"%d\" y=\"%d\" dir=\"%d\"/>\n",
          getType_Move(move),
          getStartX_Move (move),
          getStartY_Move (move),
          getDirection_Move (move));

}

void print_move_node ( pMoveList_t node ) {
  if ( node == NULL )
    printf ("<node>NULL</node>");
  else
    {
      printf ("<node>\n  ");
      print_move (node->move);
      printf ("  <next adr=\"%x\"/>\n", node->pnext);
      printf ("</node>\n");
    }
}

void print_move_list ( pMoveList_t list ) {

  pMoveList_t runner;

  if ( list == NULL )
    printf ("<movelist/>\n");
  else
    {
      printf ("<movelist>\n");
      for (
           runner = list;
           runner != NULL;
           runner = runner->pnext
           )
        print_move_node (runner);
      printf ("</movelist>\n");
    }
}
