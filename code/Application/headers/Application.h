#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../headers/ApplicationInterface.h"
#include "Camera.h"
#include "Scene.h"
#include <vector>

class Application : public ApplicationInterface {
public:
  Application();

  bool Event(char event_, const void *data_) override;
  bool Update(int dt_) override;

  void Draw() const override;
  void RenderGui() override;

  void Init() override;
  bool Load(int argc_, char **argv_) override;

private:
  bool mExit = false;
  Camera mCamera;
  Scene mScene;
  std::vector<GameObject> mObjects;
};

#endif
