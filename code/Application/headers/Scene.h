#ifndef SCENE_H
#define SCENE_H

#include "../../Connector/headers/GameObject.h"

class Scene : public GameObject {
public:
  bool Event(char event_, const void *data_);
  void Draw() const override;

protected:
  virtual void DrawGui() const {};
};

#endif
