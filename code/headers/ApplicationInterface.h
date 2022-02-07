#ifndef IMGUI_INTERFACE_H
#define IMGUI_INTERFACE_H

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
  virtual void RenderGui(){};
  virtual void Init(){};
  virtual bool Load(int argc, char **argv) { return false; };

protected:
  unsigned char GetKey() const { return mKey; }
  int getSpecialKey() const { return mSpecialKey; }
  int GetMouseX() const { return mMouseX; }
  int GetMouseY() const { return mMouseY; }
  int GetMouseButton() const { return mMouseButton; }
  int GetMouseState() const { return mMouseState; }
  int GetWidth() const { return mWidth; }
  int GetHeight() const { return mHeight; }
  bool GetKeyPressed() const { return mKeyPressed; }
  bool GetSpecialKeyPressed() const { return mSpecialKeyPressed; }
  const UIData *GetUIData() const {
    return new UIData(mKey, mSpecialKey, mMouseX, mMouseY, mMouseButton,
                      mMouseState, mWidth, mHeight, mKeyPressed,
                      mSpecialKeyPressed);
  }

private:
  void SetResize(int width_, int height_) {
    mWidth = width_;
    mHeight = height_;
  }

  void SetMouseXY(int x_, int y_) {
    mMouseX = x_;
    mMouseY = y_;
  }

  void SetMouseButton(int button_, int state_, int x_, int y_) {
    mMouseButton = button_;
    mMouseState = state_;
    SetMouseXY(x_, y_);
  }

  void SetSpecialKey(int key_, int x_, int y_, bool press_) {
    mSpecialKey = key_;
    mSpecialKeyPressed = press_;
    SetMouseXY(x_, y_);
  }

  void SetKey(unsigned char key_, int x_, int y_, bool press_) {
    mKey = key_;
    mKeyPressed = press_;
    SetMouseXY(x_, y_);
  }

  unsigned char mKey = '\0'; // null char
  int mSpecialKey = -1, mMouseX = -1, mMouseY = -1, mMouseButton = -1,
      mMouseState = -1, mWidth = -1, mHeight = -1;
  bool mKeyPressed = false, mSpecialKeyPressed = false;

  friend class ImguiConnect;
};

#endif
