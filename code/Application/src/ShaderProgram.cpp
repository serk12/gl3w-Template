#include "../headers/Camera.h"
#include "../headers/ShaderProgram.h"

#include <glm/gtc/matrix_inverse.hpp>

ShaderProgram::ShaderProgram() : Shader() {}
ShaderProgram::~ShaderProgram() { Free(); }

void ShaderProgram::Init() { mId = glCreateProgram(); }

void ShaderProgram::AddShader(const GLuint &shader) {
  glAttachShader(mId, shader);
}

void ShaderProgram::BindFragmentOutput(const std::string &outputName) const {
  glBindAttribLocation(mId, 0, outputName.c_str());
}

GLint ShaderProgram::BindVertexAttribute(const std::string &attribName,
                                         GLint size, GLsizei stride,
                                         GLvoid *firstPointer) const {
  GLint attribPos = glGetAttribLocation(mId, attribName.c_str());
  glVertexAttribPointer(attribPos, size, GL_FLOAT, GL_FALSE, stride,
                        firstPointer);
  return attribPos;
}

void ShaderProgram::Link() {
  GLint status;
  char buffer[512];

  glLinkProgram(mId);
  glGetProgramiv(mId, GL_LINK_STATUS, &status);
  mReady = (status == GL_TRUE);
  glGetProgramInfoLog(mId, 512, NULL, buffer);
  mErrorLog.assign(buffer);
}

void ShaderProgram::Free() {
  if (mReady) {
    glDeleteProgram(mId);
    ShaderProgram::Free();
  }
}
void ShaderProgram::Use() const { glUseProgram(mId); }

void ShaderProgram::SetCamera(const std::shared_ptr<Camera> camera_) const {
  SetUniformMatrix4f("projection", camera_->GetProjectionMatrix());
  SetUniformMatrix4f("modelview", camera_->GetModelViewMatrix());
  SetUniformMatrix3f("normalMatrix", glm::inverseTranspose(glm::mat3(
                                         camera_->GetModelViewMatrix())));
  glPointSize(3.0);
}

void ShaderProgram::SetUniform1i(const std::string &uniformName, int v_) const {
  GLint location = glGetUniformLocation(mId, uniformName.c_str());
  if (location != -1)
    glUniform1i(location, v_);
}

void ShaderProgram::SetUniformf(const std::string &uniformName,
                                std::vector<float> v_) const {
  GLint location = glGetUniformLocation(mId, uniformName.c_str());
  if (location != -1) {
    switch (v_.size()) {
    case 1:
      glUniform1f(location, v_[0]);
      break;
    case 2:
      glUniform2fv(location, 1, v_.data());
      break;
    case 3:
      glUniform3fv(location, 1, v_.data());
      break;
    case 4:
      glUniform4fv(location, 1, v_.data());
      break;
    default:
      break;
    }
  }
}

void ShaderProgram::SetUniformMatrix3f(const std::string &uniformName,
                                       const glm::mat3 &mat) const {
  GLint location = glGetUniformLocation(mId, uniformName.c_str());
  if (location != -1)
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::SetUniformMatrix4f(const std::string &uniformName,
                                       const glm::mat4 &mat) const {
  GLint location = glGetUniformLocation(mId, uniformName.c_str());

  if (location != -1)
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
