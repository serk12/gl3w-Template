#ifndef SCENE_H
#define SCENE_H

#include "../../Connector/headers/GameObject.h"

class Scene : public GameObject {
public:
  bool Event(char event_) override;
  void Draw() const override final;

protected:
  virtual void DrawGui() const {};
};

#endif
