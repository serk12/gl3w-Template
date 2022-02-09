#ifndef SHADER_GENERATOR_H
#define SHADER_GENERATOR_H

#include <GL/gl3w.h>
#include <memory>
#include <string>
#include <vector>

class ShaderProgram;

class Shader {
public:
  Shader() : mId(0), mReady(false) {}
  virtual void Free() { mReady = false; };

  GLuint ProgramId() const { return mId; }
  bool IsReady() const { return mReady; }
  const std::string &Log() const { return mErrorLog; }

protected:
  GLuint mId;
  bool mReady;
  std::string mErrorLog;
};

namespace ShaderGenerator {
enum ShaderType : GLuint {
  VERTEX_SHADER = GL_VERTEX_SHADER,
  FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

using ProgramDataList = std::vector<std::pair<ShaderType, std::string>>;
using ProgramList = std::vector<std::shared_ptr<ShaderProgram>>;

class ShaderCode : public Shader {
public:
  ShaderCode();
  ~ShaderCode();
  void Free() override;
  // These methods should be called with an active OpenGL context
  void InitFromSource(const ShaderType type_, const std::string &source_);
  bool InitFromFile(const ShaderType type_, const std::string &filename_);
};

ProgramList InitShaderList(const std::vector<ProgramDataList> &);
}; // namespace ShaderGenerator

#endif
