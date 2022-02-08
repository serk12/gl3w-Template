#ifndef HANBEI_GUI_H
#define HANBEI_GUI_H

#include "../../Application/headers/Scene.h"

class HanbeiGui : public Scene {
public:
  HanbeiGui();
  void DrawGui() const override;

private:
  mutable int mValue = 5;
};

#endif
