#ifndef HANBEI_GUI_H
#define HANBEI_GUI_H

#include "../../Application/headers/Scene.h"

class AppGui : public Scene {
public:
  AppGui();
  void DrawGui() const override;

private:
  mutable int mValue = 5;
};

#endif
