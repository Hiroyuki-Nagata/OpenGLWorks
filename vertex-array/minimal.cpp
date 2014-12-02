#ifdef _WIN32
   #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>

const GLfloat vertex[] = {
  -0.9 , 0.9 , 0.9 , 0.9 , 0 , -0.9
};

void disp( void ) {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2 , GL_FLOAT , 0 , vertex);

  glBegin(GL_POLYGON); {
    int i;
    for(i = 0 ; i < 3 ; i++) glArrayElement(i);
  } glEnd();

  glFlush();
}

int main(int argc , char ** argv) {
  glutInit(&argc , argv);
  glutInitWindowPosition(100 , 50);
  glutInitWindowSize(400 , 300);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

  glutCreateWindow("Kitty on your lap");
  glutDisplayFunc(disp);

  glutMainLoop();
  return 0;
}
