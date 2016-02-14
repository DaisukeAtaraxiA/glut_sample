#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace {

bool mouse_l = false;
int mouse_pos[2]{};
double angle[2]{};

void display() {
  glClearColor(0, 0, 0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotated(angle[0], 1.0, 0.0, 0.0);
  glRotated(angle[1], 0.0, 1.0, 0.0);

  glColor3f(0.5, 0.1, 0.2);
  glBegin(GL_POLYGON);
  glVertex2f(-0.5, -0.5);
  glVertex2f(-0.5, 0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, -0.5);
  glEnd();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case '\033':  // ESC key
      exit(0);
      break;
    default:
      break;
  }
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
				mouse_pos[0] = x;
				mouse_pos[1] = y;
				mouse_l = true;
      }
      if (state == GLUT_UP) {
				mouse_l = false;
      }
      break;
    default:
      break;
  }
}

void motion(int x, int y) {
  if (mouse_l) {
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int width = viewport[2];
    int height = viewport[3];
    double theta[2]{};
    if (height > 0) {
      theta[0] = static_cast<double>(y - mouse_pos[1]) * 180.0 / height;
    }
    if (width > 0) {
      theta[1] = static_cast<double>(x - mouse_pos[0]) * 180.0 / width;
    }
    mouse_pos[0] = x;
    mouse_pos[1] = y;
    angle[0] += theta[0];
    angle[1] += theta[1];
    glutPostRedisplay();
  }
}

void resize(int width, int height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0);
}

}  // namespace

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("glut_sample");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutReshapeFunc(resize);
  glutMainLoop();
  return 0;
}
