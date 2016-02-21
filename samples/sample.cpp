#include "glut_sample/glut_application.h"

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

namespace {

void display() {
  glColor3f(0.5f, 0.1f, 0.2f);
  glBegin(GL_POLYGON);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(-0.5f, 0.5f);
  glVertex2f(0.5f, 0.5f);
  glVertex2f(0.5f, -0.5f);
  glEnd();
}

}  // namespace

int main(int argc, char **argv) {
  GlutApplication app(argc, argv);
  app.setRedrawFunction(display);
  return app.exec();
}
