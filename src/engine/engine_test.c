/**
 * engine_test.c
 * jaH, 2 April 2003
 *
 * A simple test for the engine. A shell for the engine.
 *
 */

#include "test_utility.h"
#include "search.h"

Board_t b;

static void search_board ();
static void move ();

int main ()
{
	b = getInitialBoard ();
	int command;
	while ((command = getchar ()) != 'x')
	{
		switch (command) {
		case 'p': 
			print_board (b);
			break;
		case 's':
			search_board ();
			break;
		case 'm':
			move ();
			break;
		}
	}	
	return 0;
}

static void search_board ()
{
	int depth;
	Move_t move;
	int score;
	
	printf ("Depth: ");
	scanf ("%d", &depth);
	score = search (b, depth, &move);
	printf ("Score: %d\n", score);
	print_move (move);
}

static void move ()
{
	int type, x, y, dir;
	printf ("Type: ");
	scanf ("%d", &type);
	printf ("X: ");
	scanf ("%d", &x);
	printf ("Y: ");
	scanf ("%d", &y);
	printf ("Dir: ");
	scanf ("%d", &dir);
	b = transform_Move (b, create_Move(type, x, y, dir));
}
