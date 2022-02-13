#include "../headers/FlatMesh.h"

namespace ZipUtils {
#include <zip.h>
};
#include <iostream>

FlatMesh::FlatMesh() : Model(), mHeight(0), mWidth(0) {}

// void FlatMesh::Draw() const {
//   glBindVertexArray(mVao);
//   glEnableVertexAttribArray(mPosLocation);
//   glEnableVertexAttribArray(mNormalLocation);
//   glEnableVertexAttribArray(mColorLocation);
//   glDrawArrays(GL_POINTS, 0, mPoints.size());
//   glBindVertexArray(0);
// }

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
  mWidth = 1024;
  mHeight = resultSize / 1024;
  return true;
}

void FlatMesh::SendToOpenGL(const std::shared_ptr<ShaderProgram> program_) {
  // calculate point, normal triangles and color
  for (size_t i = 0; i < mHeightMap.size(); ++i) {
    auto xy = IndexToMatrix(i);
    mPoints.push_back(glm::vec3(xy.first, mHeightMap[i], xy.second));
    if (xy.second > 0 && xy.first > 0) {
      if (xy.first % 2 == 0) {
        mTriangles.push_back(i);
        mTriangles.push_back(i + mHeight);
        mTriangles.push_back(i + 1);
      } else {
        mTriangles.push_back(i);
        mTriangles.push_back(i - 1 + mHeight);
        mTriangles.push_back(i + mHeight);
      }
    }
    mNormals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    mColors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  }
  Model::SendToOpenGL(program_);
}
