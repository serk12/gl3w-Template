#include "../headers/ShaderGenerator.h"
#include "../headers/ShaderProgram.h"
#include <fstream>
#include <iostream>

namespace ShaderGenerator {
ShaderCode::ShaderCode() : Shader() {}
ShaderCode::~ShaderCode() { Free(); }

void ShaderCode::Free() {
  if (mReady) {
    glDeleteShader(mId);
    Shader::Free();
  }
}

void ShaderCode::InitFromSource(const ShaderType type_,
                                const std::string &source_) {
  const char *sourcePtr = source_.c_str();
  GLint status;
  char buffer[512];

  mId = glCreateShader(type_);
  if (mId == 0)
    return;
  glShaderSource(mId, 1, &sourcePtr, NULL);
  glCompileShader(mId);
  glGetShaderiv(mId, GL_COMPILE_STATUS, &status);
  mReady = (status == GL_TRUE);
  glGetShaderInfoLog(mId, 512, NULL, buffer);
  mErrorLog.assign(buffer);
}

bool ShaderCode::InitFromFile(const ShaderType type_,
                              const std::string &filename_) {
  std::ifstream fin;
  fin.open(filename_.c_str());
  if (!fin.is_open())
    return false;
  std::string shaderSource;
  shaderSource.assign(std::istreambuf_iterator<char>(fin),
                      std::istreambuf_iterator<char>());
  InitFromSource(type_, shaderSource);
  return true;
}

std::vector<ShaderProgram *>
InitShaderList(const std::vector<ProgramList> &list_) {
  std::vector<ShaderProgram *> result;
  for (const auto &programList : list_) {
    ShaderProgram *program = new ShaderProgram();
    result.push_back(program);
    program->Init();
    for (const auto &programInfo : programList) {
      ShaderCode code;
      code.InitFromFile(programInfo.first, programInfo.second);
      if (code.IsReady()) {
        program->AddShader(code.ProgramId());
      } else {
        std::cout << "Shader error: " << programInfo.second << std::endl;
        std::cout << code.Log() << std::endl;
      }
      code.Free();
    }
    program->Link();
    if (!program->IsReady()) {
      std::cout << "Shader linking error" << std::endl;
      std::cout << program->Log() << std::endl << std::endl;
    }
    program->BindFragmentOutput("outColor");
  }
  return result;
}

}; // namespace ShaderGenerator
