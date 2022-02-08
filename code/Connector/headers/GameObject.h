#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

enum UIEvent : char { Key, SpecialKey, MouseMove, MouseClick, Resize };

struct UIData {
  unsigned char key;
  int specialKey, mouseX, mouseY, mouseButton, mouseState, width, height;
  bool keyPressed, specialKeyPressed;

  UIData(unsigned char key_, int specialKey_, int mouseX_, int mouseY_,
         int mouseButton_, int mouseState_, int width_, int height_,
         bool keyPressed_, bool specialKeyPressed_)
      : key(key_), specialKey(specialKey_), mouseX(mouseX_), mouseY(mouseY_),
        mouseButton(mouseButton_), mouseState(mouseState_), width(width_),
        height(height_), keyPressed(keyPressed_),
        specialKeyPressed(specialKeyPressed_) {}
};

// game object pattern
class GameObject {
public:
  // Chain of Responsibility
  virtual bool Event(char event_, const void *eventData_ = nullptr) {
    return false;
  };
  // exit application
  virtual bool Update(int dt_) { return false; };
  virtual void Draw() const {};
};

#endif
