#ifndef IMGUI_CONNECT_H
#define IMGUI_CONNECT_H

class ImguiInterface;

// this could be a namespace but maybe a class is usefull...
class ImguiConnect {
public:
  ImguiConnect(ImguiInterface *application, int argc, char **argv);

private:
  static void KeyPressed(unsigned char key, int x, int y);
  static void KeyReleased(unsigned char key, int x, int y);
  static void SpecialKeyPressed(int key, int x, int y);
  static void SpecialKeyReleased(int key, int x, int y);
  static void MouseMove(int x, int y);
  static void MouseCallBack(int button, int state, int x, int y);
  static void ResizeCallback(int width, int height);
  static void RenderGui();
  static void DrawCallback();
  static void IdleCallback();

  inline static ImguiInterface *mApplication = nullptr;
  inline static int mPrevTime = -1;
};

#endif
