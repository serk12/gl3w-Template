#ifndef SCENE_H
#define SCENE_H

#include "../../headers/GameObject.h"

class Scene : public GameObject {
public:
  void InitShaders();
  void DrawGui();
  bool Event(char event_, const void *data_);

private:
  int mValue = 5;
};

#endif
