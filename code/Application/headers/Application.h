#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../Connector/headers/ApplicationInterface.h"
#include <memory>
#include <vector>

class Camera;
class Scene;
class Model;
class ShaderProgram;

class Application : public ApplicationInterface {
public:
  Application();
  void Init() override;

  bool Event(char event_) override;
  bool Update(int dt_) override;

  void Draw() const override;

protected:
  bool mExit = false;

  std::shared_ptr<Camera> mCamera;
  std::shared_ptr<Scene> mScene;
  std::vector<std::shared_ptr<Model>> mObjects;
  std::vector<std::shared_ptr<ShaderProgram>> mShaders;
};

#endif
