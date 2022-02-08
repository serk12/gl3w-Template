#ifndef SHADER_H
#define SHADER_H

#include "ShaderGenerator.h"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

class ShaderProgram : public Shader {
public:
  ShaderProgram();
  ~ShaderProgram();

  void Init();
  void AddShader(const GLuint &shader_);
  void BindFragmentOutput(const std::string &outputName_) const;
  GLint BindVertexAttribute(const std::string &attribName_, GLint size_,
                            GLsizei stride_, GLvoid *firstPointer_) const;
  void Link();
  void Free() override;
  void Use() const;

  void SetUniform1i(const std::string &uniformName_, int v_) const;
  void SetUniformf(const std::string &uniformName_,
                   std::vector<float> v_) const;
  void SetUniformMatrix3f(const std::string &uniformName_,
                          const glm::mat3 &mat_) const;
  void SetUniformMatrix4f(const std::string &uniformName_,
                          const glm::mat4 &mat_) const;
};

#endif
