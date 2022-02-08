#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../Connector/headers/ApplicationInterface.h"
#include "Camera.h"
#include "Model.h"
#include "Scene.h"
#include <list>

class Application : public ApplicationInterface {
public:
  Application();
  void Init() override;

  bool Event(char event_, const void *data_) override;
  bool Update(int dt_) override;

  void Draw() const override;

protected:
  bool mExit = false;

  Camera mCamera;
  Scene *mScene;
  std::list<Model *> mObjects;
};

#endif
