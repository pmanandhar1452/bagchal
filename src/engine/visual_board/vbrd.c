/**
 * vbrd.c
 * jaH
 * 15 Oct 2002
 *
 * A visual baagchal board in OpenGL that allows one to 
 * generate code to construct the board for testing.
 */

#include <GL/glut.h>
#include <stdio.h>

unsigned char model[5][5]; // the model of the board

int width, height;

void writeModel (int);
int get_num_shikaar (void);
void init_model (void);
void init_menu (void);
void init_void (void);
void mouse_pressed (int button, int state, int x, int y);
void display (void);
void draw_empty_board (void);
void transform_to_model (int x, int y, int *xt, int *yt);
void toggle_model (int x, int y);
void reshape (int, int);
void draw_pieces (void);
void drawShikaar (int, int);
void drawTiger (int, int);

/**
 * writes the model to disk.
 */
void writeModel (int value) {
  
  int i, j;
  int num_sh, num_left;
  FILE * fp;

  fp = fopen ("model.out", "w");
  if (fp == NULL) {
    printf ("Error in opening file!!!\n");
    return;
  }

  // create an empty board
  fprintf (fp, "b = getEmptyBoard ();\n");
  
  // add the pieces to the board
  for (i = 0; i < 5; i++)
  for (j = 0; j < 5; j++)
    {
      if (model [i][j] == 1) {
        fprintf (fp, "setPieceAtPosition_Board (&b, PIECE_T_SHIKAAR, %d, %d);\n", i, j);
      }
      else if (model [i][j] == 2) {
        fprintf (fp, "setPieceAtPosition_Board (&b, PIECE_T_TIGER, %d, %d);\n", i, j);
      }
    }

  // set the number killed and number left
  num_sh = get_num_shikaar ();
  num_left = 20 - num_sh;
  
  fprintf (fp, "setNumberOfShikaarKilled_Board (&b, 0);\n");
  fprintf (fp, "setNumberOfShikaarLeft_Board (&b, %d);\n", num_left);
  fclose (fp);

}

int get_num_shikaar (void) {
  
  int n, i, j;

  n = 0;
  for (i = 0; i < 5; i++)
  for (j = 0; j < 5; j++)
    {
      if (model [i][j] == 1) n++;
    }

  return n;

}

void init_model (void) {
  int i, j;
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      model[i][j] = 0;
}

void init_menu (void) {
  glutCreateMenu (writeModel);
  glutAddMenuEntry ("Write Model Data", 0);
  glutAttachMenu (GLUT_RIGHT_BUTTON);
}


void init (void) {
  width = height = 550;
  init_model();
  init_menu ();  
  glEnable (GL_LINE_SMOOTH);

}

void mouse_pressed (int button, int state, int x, int y) {
  int xm, ym;
  if ( state != 0 ) return;
  transform_to_model (x, y, &xm, &ym);
  toggle_model (xm, ym);
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

void toggle_model (int x, int y) {
  if ( x < 0 || x > 4 || y < 0 || y > 4 ) return;
  model [x][y] = (model [x][y] + 1) % 3;
}

void draw_pieces (void) {
  
  int i, j;

  for (i = 0; i < 5; i++)
  for (j = 0; j < 5; j++)
    {
      if (model [i][j] == 1) drawShikaar (i, j);
      else if (model [i][j] == 2) drawTiger (i, j);
      
    }
  
}

void drawShikaar (int i, int j) {

  float x, y;
  x = (i-2)*0.4;
  y = (j-2)*0.4;
  
  glColor3f (0.0, 1.0, 0.0);
  glRectf(x-0.05, y-0.05, x+0.05, y+0.05);

}

void drawTiger (int i, int j) {

  float x, y;
  x = (i-2)*0.4;
  y = (j-2)*0.4;
  
  glColor3f (1.0, 0.0, 0.0);
  glRectf(x-0.1, y-0.1, x+0.1, y+0.1);

}
