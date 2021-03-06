/* c1-2.c */

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#define KEY_ESC 27

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // 描画物体に白色を設定
  glColor3f(1.0, 1.0, 1.0);
  // ポリゴン（多角形平面の描画）
  glBegin(GL_POLYGON);
  glVertex3f(0.5, 0.5, 0.0);
  glVertex3f(-0.5, 0.5, 0.0);
  glVertex3f(-0.5, -0.5, 0.0);
  glVertex3f(0.5, -0.5, 0.0);
  // 描画の終了
  glEnd();

  glFlush();
}

void myKbd(unsigned char key, int x, int y)
{
  if ( key == KEY_ESC ) exit(0);
}

void myInit(char* progname)
{
  int width = 500, height = 500;

  glutInitWindowPosition(0, 0);
  glutInitWindowSize( width, height );
  glutInitDisplayMode( GLUT_RGBA );
  glutCreateWindow( progname );

  glClearColor(0.0,0.0,0.0,1.0);
  glutKeyboardFunc(myKbd);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  myInit(argv[0]);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
