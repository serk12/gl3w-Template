#ifndef IMGUI_INTERFACE_H
#define IMGUI_INTERFACE_H

#include "Context.h"
#include "GameObject.h"

// Interface - addapter pattern Application - Imgui
class ApplicationInterface : public GameObject {
public:
  // event(char event)
  // virtual void KeyPressed(unsigned char key, int x, int y){};
  // virtual void KeyReleased(unsigned char key, int x, int y){};
  // virtual void SpecialKeyPressed(int key, int x, int y){};
  // virtual void SpecialKeyReleased(int key, int x, int y){};
  // virtual void MouseMove(int x, int y){};
  // virtual void MouseCallBack(int button, int state, int x, int y){};
  // virtual void ResizeCallback(int width, int height){};
  // virtual DrawCallback() {}; // render()
  // virtual idleCallback(dt) {}; // update(dt)
  virtual void Init(){};
  virtual bool Load(int argc, char **argv) { return false; };
};

#endif
