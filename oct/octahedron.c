/*
 * octahedron.c
 */

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

void initdisplay(void)
{
  glClearColor (0.0, 0.0, 0.4, 0.0);
  // glShadeModel (GL_SMOOTH);
  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void draw(void)
{
  glBegin (GL_TRIANGLE_FAN);
  glColor3f(0.0, 0.0, 1.0);  glVertex3f(0.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);  glVertex3f(1.0, 0.0, 0.0);
  glColor3f(0.0, 1.0, 0.0);  glVertex3f(0.0, 1.0, 0.0);
  glColor3f(0.0, 1.0, 1.0);  glVertex3f(-1.0, 0.0, 0.0);
  glColor3f(1.0, 0.0, 1.0);  glVertex3f(0.0, -1.0, 0.0);
  glColor3f(0.0, 1.0, 1.0);  glVertex3f(1.0, 0.0, 0.0);
  glEnd();

  glBegin (GL_TRIANGLE_FAN);
  glColor3f(1.0, 1.0, 0.0);  glVertex3f(0.0, 0.0, -1.0);
  glColor3f(1.0, 0.0, 0.0);  glVertex3f(1.0, 0.0, 0.0);
  glColor3f(1.0, 0.0, 1.0);  glVertex3f(0.0, -1.0, 0.0);
  glColor3f(0.0, 1.0, 1.0);  glVertex3f(-1.0, 0.0, 0.0);
  glColor3f(0.0, 1.0, 0.0);  glVertex3f(0.0, 1.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);  glVertex3f(1.0, 0.0, 0.0);
  glEnd();
}

void display(void)
{
  static GLfloat rot = 0.0;
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(rot, 1.0, 1.0, 1.0);
  rot += 4.0;
  draw();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (-2.0, 2.0, -2.0, 2.0);
  //  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key){
  case 0x1b:
    exit(0);
    break;
  }
}

void idle(void)
{
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500,500); 
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  initdisplay();

  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
