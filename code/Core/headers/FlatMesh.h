#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H

#include "../../Application/headers/Model.h"

/*! \class FlatMesh
    \brief Basic 2.5D mesh

    Load a .plux file and stores it in a height matrix
*/
class FlatMesh : public Model {
public:
  FlatMesh();

  // bool Load(const std::string &filename_) override;

private:
  std::pair<size_t, size_t> IndexToMatrix(size_t i_) const {
    size_t x = i_ / mHeight;
    size_t y = i_ % mHeight;
    return std::make_pair(x, y);
  }
  size_t MatrixToIndex(size_t x_, size_t y_) const { return x_ * mHeight + y_; }

  size_t mHeight, mWidth;
};

#endif
