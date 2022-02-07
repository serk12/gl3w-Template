#ifndef SHADER_GENERATOR_H
#define SHADER_GENERATOR_H

#include <GL/gl.h>
#include <GL/gl3w.h>

enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };

class Shader {
  ShaderProgram();

  void init();
  void addShader(const Shader &shader);
  void bindFragmentOutput(const string &outputName);
  GLint bindVertexAttribute(const string &attribName, GLint size,
                            GLsizei stride, GLvoid *firstPointer);
  void link();
  void free();

  void use();

  // Pass uniforms to the associated shaders
  void setUniform1i(const string &uniformName, int v);
  void setUniform2f(const string &uniformName, float v0, float v1);
  void setUniform3f(const string &uniformName, float v0, float v1, float v2);
  void setUniform4f(const string &uniformName, float v0, float v1, float v2,
                    float v3);

  void setUniformMatrix3f(const string &uniformName, const glm::mat3 &mat);
  void setUniformMatrix4f(const string &uniformName, const glm::mat4 &mat);

  bool isLinked();
  const string &log() const;

private:
  GLuint programId;
  bool linked;
  string errorLog;
};

namespace ShaderGenerator {
Shader initFromSource(const ShaderType type, const string &source);
Shader initFromFile(const ShaderType type, const string &filename);
}; // namespace ShaderGenerator

#endif
