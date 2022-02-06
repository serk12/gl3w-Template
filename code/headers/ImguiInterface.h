#ifndef IMGUI_INTERFACE_H
#define IMGUI_INTERFACE_H

#include "GameObject.h"

class ImguiInterface : public GameObject {
public:
  virtual void KeyPressed(unsigned char key, int x, int y){};
  virtual void KeyReleased(unsigned char key, int x, int y){};
  virtual void SpecialKeyPressed(int key, int x, int y){};
  virtual void SpecialKeyReleased(int key, int x, int y){};
  virtual void MouseMove(int x, int y){};
  virtual void MouseCallBack(int button, int state, int x, int y){};
  virtual void ResizeCallback(int width, int height){};
  virtual void RenderGui(){};
  // virtual DrawCallback() {}; // render()
  // virtual idleCallback() {}; // update(dt) {};
  virtual void init(){};
  virtual bool load(int argc, char **argv) { return false; };
};

#endif
