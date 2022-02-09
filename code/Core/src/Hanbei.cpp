#include "../headers/Hanbei.h"

#include "../../Application/headers/ShaderGenerator.h"
#include "../headers/HanbeiGui.h"
#include "../headers/PointCloud.h"

Hanbei::Hanbei() : Application() {}

bool Hanbei::Load(int argc_, char **argv_) {
  mScene = std::shared_ptr<Scene>(new HanbeiGui());
  mShaders = ShaderGenerator::InitShaderList(
      {{std::make_pair(ShaderGenerator::ShaderType::VERTEX_SHADER,
                       "../Shaders/default.vert"),
        std::make_pair(ShaderGenerator::ShaderType::FRAGMENT_SHADER,
                       "../Shaders/default.frag")}});
  auto pc = std::shared_ptr<PointCloud>(new PointCloud());
  pc->Load("../models/bunny.ply");
  pc->SendToOpenGL(*mShaders.begin());
  mObjects.push_back(pc);
  return true;
}
