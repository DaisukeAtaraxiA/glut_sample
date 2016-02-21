#include "glut_sample/glut_application.h"

#include <stdlib.h>

#include <cassert>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class GlutApplication;

class GlutApplicationCore {
 public:
  static void invoke_display();
  static void invoke_keyboard(unsigned char key, int x, int y);
  static void invoke_mouse(int button, int state, int x, int y);
  static void invoke_motion(int x, int y);
  static void invoke_resize(int width, int height);

  static GlutApplication *app_;
};

GlutApplication *GlutApplicationCore::app_ = nullptr;

void GlutApplicationCore::invoke_display() {
  assert(app_ != nullptr);
  app_->display();
}

void GlutApplicationCore::invoke_keyboard(unsigned char key, int x, int y) {
  assert(app_ != nullptr);
  app_->keyboard(key, x, y);
}

void GlutApplicationCore::invoke_mouse(int button, int state, int x, int y) {
  assert(app_ != nullptr);
  app_->mouse(button, state, x, y);
}

void GlutApplicationCore::invoke_motion(int x, int y) {
  assert(app_ != nullptr);
  app_->motion(x, y);
}

void GlutApplicationCore::invoke_resize(int width, int height) {
  assert(app_ != nullptr);
  app_->resize(width, height);
}

GlutApplication::GlutApplication(int argc, char *argv[]) {
  GlutApplicationCore::app_ = this;
  redraw_function_ = []() {};
  mouse_pos[0] = 0;
  mouse_pos[1] = 0;
  angle[0] = 0;
  angle[1] = 0;
  glutInit(&argc, argv);
}

int GlutApplication::exec() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("glut_sample");
  glutDisplayFunc(&GlutApplicationCore::invoke_display);
  glutKeyboardFunc(&GlutApplicationCore::invoke_keyboard);
  glutMouseFunc(&GlutApplicationCore::invoke_mouse);
  glutMotionFunc(&GlutApplicationCore::invoke_motion);
  glutReshapeFunc(&GlutApplicationCore::invoke_resize);
  glutMainLoop();
  return 0;
}

void GlutApplication::setRedrawFunction(std::function<void(void)> func) {
  redraw_function_ = func;
}

void GlutApplication::display() {
  glClearColor(0, 0, 0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotated(angle[0], 1.0, 0.0, 0.0);
  glRotated(angle[1], 0.0, 1.0, 0.0);

  redraw_function_();

  glutSwapBuffers();
}

void GlutApplication::keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case '\033':  // ESC key
      exit(0);
      break;
    default:
      break;
  }
}

void GlutApplication::mouse(int button, int state, int x, int y) {
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

void GlutApplication::motion(int x, int y) {
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

void GlutApplication::resize(int width, int height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  GLfloat w = static_cast<GLfloat>(width);
  GLfloat h = static_cast<GLfloat>(height);
  if (w <= h) {
    glOrtho(-2, 2, -2 * h / w, 2.0 * h / w, -10.0, 10.0);
  } else {
    glOrtho(-2 * w / h, 2.0 * w / h, -2.0, 2.0, -10.0, 10.0);
  }
}
