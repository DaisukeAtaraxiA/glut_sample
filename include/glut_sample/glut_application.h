#pragma once

#include <functional>

class GlutApplication {
 public:
  GlutApplication(int argc, char *argv[]);

  int exec();
  void setRedrawFunction(std::function<void(void)> func);

 private:
  GlutApplication(const GlutApplication&);
  GlutApplication &operator=(const GlutApplication&);

  void display();
  void keyboard(unsigned char key, int x, int y);
  void mouse(int button, int state, int x, int y);
  void motion(int x, int y);
  void resize(int width, int height);

  std::function<void(void)> redraw_function_; 
  bool mouse_l = false;
  int mouse_pos[2];
  double angle[2];

  friend class GlutApplicationCore;
};
