#include "../headers/FlatMesh.h"

namespace ZipUtils {
#include <zip.h>
};
#include <iostream>

FlatMesh::FlatMesh() : Model(), mHeight(0), mWidth(0) {}

void FlatMesh::Draw() const {
  glBindVertexArray(mVao);
  glEnableVertexAttribArray(mPosLocation);
  glEnableVertexAttribArray(mNormalLocation);
  glEnableVertexAttribArray(mColorLocation);
  glDrawArrays(GL_POINTS, 0, mPoints.size());
  glBindVertexArray(0);
}

bool FlatMesh::Load(const std::string &filename_) {
  const std::string HEIGHT_MAP = "LAYER_0.raw";
  // open zip
  int error;
  ZipUtils::zip *pZip = ZipUtils::zip_open(filename_.c_str(), 0, &error);
  if (pZip == nullptr) {
    return false;
  }
  // get size
  struct ZipUtils::zip_stat stats;
  int res =
      ZipUtils::zip_stat(pZip, HEIGHT_MAP.c_str(), ZIP_FL_ENC_GUESS, &stats);
  if (res == -1)
    return false;
  ZipUtils::zip_int64_t size = stats.size;
  // get height map
  struct ZipUtils::zip_file *insideFile =
      ZipUtils::zip_fopen(pZip, HEIGHT_MAP.c_str(), 0);
  // load height map
  mHeightMap.resize(size / sizeof(float));
  ZipUtils::zip_int64_t resultSize =
      ZipUtils::zip_fread(insideFile, &mHeightMap[0], size);
  // close zip
  ZipUtils::zip_fclose(insideFile);
  // check size is correct
  if (resultSize != size) {
    return false;
  }
  int aux = resultSize / 1024;
  mWidth = aux < 1024 ? aux : 1024;
  mHeight = aux > 1024 ? aux : 1024;
  return true;
}

void FlatMesh::SendToOpenGL(const std::shared_ptr<ShaderProgram> program_) {
  // calculate point, normal triangles and color
  for (size_t i = 0; i < mHeightMap.size(); ++i) {
    std::pair<size_t, size_t> xy = IndexToMatrix(i);
    size_t x = xy.first;
    size_t y = xy.second;
    mPoints.push_back(glm::vec3(x * 0.01f, mHeightMap[i] * 0.2f, y * 0.01f));
    mNormals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    mColors.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  }

  // for (size_t i = 0; i < mWidth; ++i) {
  //   for (size_t j = 0; j < mHeight; ++j) {
  //     if (i + 1 < mWidth && j + 1 < mWidth) {
  //       mTriangles.push_back(MatrixToIndex(i, j));
  //       mTriangles.push_back(MatrixToIndex(i + 1, j));
  //       mTriangles.push_back(MatrixToIndex(i, j + 1));
  //     }
  //     if (i > 0 && j > 0) {
  //       mTriangles.push_back(MatrixToIndex(i, j));
  //       mTriangles.push_back(MatrixToIndex(i - 1, j));
  //       mTriangles.push_back(MatrixToIndex(i, j - 1));
  //     }
  //   }
  // }
  Model::SendToOpenGL(program_);
}
