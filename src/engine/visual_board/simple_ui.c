/**
 * vbrd.c
 * jaH
 * 3 April 2003
 *
 * A simple board that interacts with the bagchal engine in
 * a direct way.
 * 
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "../search.h"
#include "../test_utility.h"
#include "../evaluation.h"
#include "../generator.h"
#include "../engine.h"

#define SEARCH_DEPTH 3

Board_t board;
int move_state, move_sx, move_sy;
int width, height;

void init_model (void);
void mouse_pressed (int button, int state, int x, int y);
void display (void);
void draw_empty_board (void);
void transform_to_model (int x, int y, int *xt, int *yt);
void reshape (int, int);
void draw_pieces (void);
void drawShikaar (int, int);
void drawTiger (int, int);
int get_dir (int, int);
int getSearchDepth (Board_t);

void init_model (void) {
	board = getInitialBoard ();
	setPieceAtPosition_Board (&board, PIECE_T_SHIKAAR, 0, 2);
	setNumberOfShikaarLeft_Board (&board, 19);
	setTurn_Board (&board, TURN_T_TIGER);
	move_state = 0;
}

void init (void) {
  initialize_engine ();
  width = height = 550;
  init_model();
  glEnable (GL_LINE_SMOOTH);
}

void mouse_pressed (int button, int state, int x, int y) {
  int xm, ym;
  if ( state != 0 ) return;
  transform_to_model (x, y, &xm, &ym);
  if (move_state == 0) {
	  move_state = 1;
	  move_sx = xm;
	  move_sy = ym;
  } else
  {
	  int dir, type;
	  Move_t m;
	  move_state = 0;
	  dir = get_dir (xm, ym);
	  if (dir == -1)
	  {
		glutPostRedisplay ();
		return;
	  }
	  if (abs (xm - move_sx) == 2 || abs(ym - move_sy) == 2)
		  type = MOVE_T_TIGER_TAKE;
	  else type = MOVE_T_TIGER_NORMAL;
	  m = create_Move (type, move_sx, move_sy, dir);
	  if (isValid_Move (board, m))
  	  {
		int score;
		Move_t new_move;
		board = transform_Move (board, m);
		print_board (board);
		print_move (m);
		score = evaluate_Static (board);
		if (score == EVAL_POS_INFTY || score == EVAL_NEG_INFTY)
		{
			print_board (board);
			printf ("The End");
			exit (0);
		}
		display ();
		score = search (board, getSearchDepth(board), &new_move);
		print_move (new_move);
		printf ("Score = %d", score);
		score = evaluate_Static (board);
		if (score == EVAL_POS_INFTY || score == EVAL_NEG_INFTY)
		{
			print_board (board);
			printf ("\nThe End\n");
			exit (0);
		}
		new_move = randomizeMove (board, new_move);
		print_move (new_move);
		board = transform_Move (board, new_move);
		print_board (board);
	  }
  }
  glutPostRedisplay ();
}

void display (void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw_empty_board ();
  draw_pieces ();
  glutSwapBuffers ();
}


void reshape (int w, int h) 
{
  width = w; height = h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (550, 550);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Bagchaal Test");
	init ();
        glutMouseFunc (mouse_pressed);
	glutDisplayFunc (display);
        glutReshapeFunc (reshape);
	glutMainLoop ();
	return 0;
}

void draw_empty_board (void) {

  glColor3f (1.0, 1.0, 1.0);
  glBegin (GL_LINE_STRIP);

  glVertex2f (-0.8, -0.8);
  glVertex2f (0.8, -0.8);
  glVertex2f (0.8, 0.8);
  glVertex2f (-0.8, 0.8);
  glVertex2f (-0.8, -0.8);
  glVertex2f (0.8, 0.8);
  glVertex2f (-0.8, 0.8);
  glVertex2f (0.8, -0.8);

  glEnd ();

  glBegin (GL_LINE_STRIP);

  glVertex2f (-0.8, 0.0);
  glVertex2f (0.0, -0.8);
  glVertex2f (0.8, 0.0);
  glVertex2f (0.0, 0.8);
  glVertex2f (-0.8, 0.0);
  glVertex2f (0.8, 0.0);
  glVertex2f (0.0, -0.8);
  glVertex2f (0.0, 0.8);

  glEnd ();

  glBegin (GL_LINES);

  glVertex2f (-0.8, -0.4);
  glVertex2f (0.8, -0.4);
  glVertex2f (0.8, 0.4);
  glVertex2f (-0.8, 0.4);
  glVertex2f (-0.4, -0.8);
  glVertex2f (-0.4, 0.8);
  glVertex2f (0.4, 0.8);
  glVertex2f (0.4, -0.8);

  glEnd ();
}

void transform_to_model (int x, int y, int *xm, int *ym) {

  int xt, yt;

  xt = (int)((5.0*x)/width);
  yt = (int)((5.0*y)/height);
  
  *xm = xt;
  *ym = 4 - yt;
  
}

void draw_pieces (void) {
  
  int i, j;

  for (i = 0; i < 5; i++)
  for (j = 0; j < 5; j++)
    {
	Piece_t p = getPieceAtPosition_Board (board, i, j);
      	if (p == PIECE_T_SHIKAAR) 
	      drawShikaar (i, j);
 	else if (p == PIECE_T_TIGER) drawTiger (i, j);
    }
  
}

void drawShikaar (int i, int j) {

  float x, y;
  x = (i-2)*0.4;
  y = (j-2)*0.4;
  
  if (move_state == 1 && i == move_sx && j == move_sy)
	  glColor3f (0.0, 0.0, 1.0);
  else
	  glColor3f (0.0, 1.0, 0.0);
  glRectf(x-0.05, y-0.05, x+0.05, y+0.05);

}

void drawTiger (int i, int j) {

  float x, y;
  x = (i-2)*0.4;
  y = (j-2)*0.4;
  
  if (move_state == 1 && i == move_sx && j == move_sy)
	  glColor3f (0.0, 0.0, 1.0);
  else
  	glColor3f (1.0, 0.0, 0.0);
  glRectf(x-0.1, y-0.1, x+0.1, y+0.1);

}

int get_dir (int x, int y)
{	
	int delx, dely;
	delx = x - move_sx;
	dely = y - move_sy;
	if (delx == 0)
	{
		if (dely == 0)
			return -1;	
		else if (dely < 0)
			return MOVE_DIR_T_0N;
		else if (dely > 0)
			return MOVE_DIR_T_0P;
			
	}
	else if (delx < 0)
	{
		if (dely == 0)
			return MOVE_DIR_T_N0;	
		else if (dely < 0)
			return MOVE_DIR_T_NN;
		else if (dely > 0)
			return MOVE_DIR_T_NP;
	}		
	else if (delx > 0)
	{
		if (dely == 0)
			return MOVE_DIR_T_P0;
		else if (dely < 0)
			return MOVE_DIR_T_PN;
		else if (dely > 0)
			return MOVE_DIR_T_PP;
	}
	return -1;	
}

int getSearchDepth (Board_t b)
{
	pMoveList_t moves = generateUniqueNextMoves (b);
	int c = getNodeCount_MoveList (moves);
	destroy_MoveList (&moves);
	if (c > 10) return SEARCH_DEPTH;
	else if (c > 5) return SEARCH_DEPTH*2;
	else return SEARCH_DEPTH*3;
}
