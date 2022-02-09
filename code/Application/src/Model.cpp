#include "../headers/Model.h"
#include "../headers/ShaderProgram.h"
#include <fstream>
#include <iostream>

bool Model::Load(const std::string &filename_) {
  std::ifstream fin;
  char line[100];
  int nPoints;
  glm::vec3 P, N = glm::vec3(0.f, 0.f, 1.f);
  bool bNormals = false;

  fin.open(filename_.c_str());
  if (!fin.is_open())
    return false;

  // Check file format
  fin.getline(line, 100);
  if (strncmp(line, "ply", strlen("ply")))
    return false;
  fin.getline(line, 100);
  if (strncmp(line, "format ascii 1.0", strlen("format ascii 1.0")))
    return false;

  // Read # points & skip the rest of the header
  fin.getline(line, 100);
  while (strncmp(line, "end_header", strlen("end_header")) != 0) {
    if (strncmp(line, "element vertex", strlen("element vertex")) == 0)
      nPoints = atoi(&line[strlen("element vertex")]);
    else if (strncmp(line, "property float nx", strlen("property float nx")) ==
             0)
      bNormals = true;
    fin.getline(line, 100);
  }

  // Read point cloud
  mPoints.clear();
  for (unsigned int i = 0; i < nPoints; i++) {
    fin >> P.x >> P.y >> P.z;
    if (bNormals)
      fin >> N.x >> N.y >> N.z;
    mTriangles.push_back(mPoints.size());
    mPoints.push_back(P);
    mNormals.push_back(N);
  }
  std::cout << "Model loaded: " << mPoints.size() << std::endl;
  mColors.resize(mPoints.size(), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

  return true;
}

void Model::SendToOpenGL(const std::shared_ptr<ShaderProgram> program_) {
  // Send data to OpenGL
  if (!mGLObjsInit) {
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
    glGenBuffers(1, &mVboPosition);
    glGenBuffers(1, &mVboNormal);
    glGenBuffers(1, &mVboColor);
    glGenBuffers(1, &mEbo);
  } else {
    glBindVertexArray(mVao);
  }
  mGLObjsInit = true;
  // VBO for vertex positions
  glBindBuffer(GL_ARRAY_BUFFER, mVboPosition);
  glBufferData(GL_ARRAY_BUFFER, 3 * mPoints.size() * sizeof(float),
               &mPoints[0].x, GL_STATIC_DRAW);
  mPosLocation = program_->BindVertexAttribute("position", 3, 0, 0);
  // VBO for vertex normals
  glBindBuffer(GL_ARRAY_BUFFER, mVboNormal);
  glBufferData(GL_ARRAY_BUFFER, 3 * mNormals.size() * sizeof(float),
               &mNormals[0].x, GL_STATIC_DRAW);
  mNormalLocation = program_->BindVertexAttribute("normal", 3, 0, 0);
  // VBO for vertex normals
  glBindBuffer(GL_ARRAY_BUFFER, mVboColor);
  glBufferData(GL_ARRAY_BUFFER, 4 * mColors.size() * sizeof(float),
               &mColors[0].x, GL_STATIC_DRAW);
  mColorLocation = program_->BindVertexAttribute("color", 4, 0, 0);
  // EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * mTriangles.size(), &mTriangles[0],
               GL_STATIC_DRAW);
}

void Model::Draw() const {
  glBindVertexArray(mVao);
  glEnableVertexAttribArray(mPosLocation);
  glEnableVertexAttribArray(mNormalLocation);
  glEnableVertexAttribArray(mColorLocation);
  glDrawArrays(GL_POINTS, 0, mPoints.size());
}

void Model::Free() {
  glDeleteBuffers(1, &mVboPosition);
  glDeleteBuffers(1, &mVboNormal);
  glDeleteBuffers(1, &mVboColor);
  glDeleteVertexArrays(1, &mVao);
  glDeleteBuffers(1, &mEbo);
  mPoints.clear();
  mNormals.clear();
  mTriangles.clear();
  mColors.clear();
}
