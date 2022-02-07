#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../headers/ApplicationInterface.h"
#include "Camera.h"
#include "Scene.h"
#include <vector>

class Application : public ApplicationInterface {
public:
  Application();

  bool Event(char event) override;
  bool Update(int dt) override;

  void Draw() const override;
  void RenderGui() override;

  void Init() override;
  bool Load(int argc, char **argv) override;

private:
  bool mExit = false;
  Camera mCamera;
  Scene scene;
  std::vector<GameObject> mObjects;
};

#endif
