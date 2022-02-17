#include "../headers/App.h"

#include "../../Application/headers/ShaderGenerator.h"
#include "../headers/AppGui.h"
#include "../headers/Mesh.h"

App::App() : Application() {}

bool App::Load(int argc_, char **argv_) {
  mScene = std::shared_ptr<Scene>(new AppGui());
  mShaders = ShaderGenerator::InitShaderList(
      {{std::make_pair(ShaderGenerator::ShaderType::VERTEX_SHADER,
                       "../Shaders/default.vert"),
        std::make_pair(ShaderGenerator::ShaderType::FRAGMENT_SHADER,
                       "../Shaders/default.frag")}});
  auto pc = std::shared_ptr<Mesh>(new Mesh());
  pc->Load("../models/bunny.ply");
  pc->SendToOpenGL(*mShaders.begin());
  mObjects.push_back(pc);
  return true;
}
