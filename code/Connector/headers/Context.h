#ifndef CONTEXT_H
#define CONTEXT_H

enum UIEvent : char { Key, SpecialKey, MouseMove, MouseClick, Resize };

struct UIData {
  UIData() : UIData('0', -1, -1, -1, -1, -1, 640, 480, false, false) {}
  UIData(unsigned char key_, int specialKey_, int mouseX_, int mouseY_,
         int mouseButton_, int mouseState_, int width_, int height_,
         bool keyPressed_, bool specialKeyPressed_)
      : key(key_), specialKey(specialKey_), mouseX(mouseX_), mouseY(mouseY_),
        mouseButton(mouseButton_), mouseState(mouseState_), width(width_),
        height(height_), keyPressed(keyPressed_),
        specialKeyPressed(specialKeyPressed_) {}

  unsigned char GetKey() { return key; }
  int GetSpecialKey() { return specialKey; }
  int GetMouseX() { return mouseX; }
  int GetMouseY() { return mouseY; }
  int GetMouseButton() { return mouseButton; }
  int GetMouseState() { return mouseState; }
  int GetWidth() { return width; }
  int GetHeight() { return height; }
  bool GetKeyPressed() { return keyPressed; }
  bool GetSpecialKeyPressed() { return specialKeyPressed; }

private:
  unsigned char key;
  int specialKey, mouseX, mouseY, mouseButton, mouseState, width, height;
  bool keyPressed, specialKeyPressed;

  friend class ImguiConnect;
};

/*! Context namespace static and stackable */
namespace Context {
void PushEvent(char event_);
char PopEvent();
bool EventsEmpty();
UIData &GetUIData();
}; // namespace Context

#endif
