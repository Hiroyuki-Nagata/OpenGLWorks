#include <GL/glut.h> 
#include <stdlib.h>

#ifdef _WIN32
   #include <windows.h>
#endif

const char title[] = "窓を開くまで--立方体の表示";
GLfloat eye[]={ 40.0, 10.0, 20.0 };

//
// Reference: http://mail2.nara-edu.ac.jp/~asait/open_gl/opengl.htm
//
void myinit(void)
{
  GLfloat light_position[] = { 100.0, 100.0, 100.0, 1.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glutSolidCube(2.0);
  glFlush();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(10.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow(title);
  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutMainLoop();
}
