#ifndef CAMERA_H
#define CAMERA_H

#include "../../Connector/headers/GameObject.h"

#include <glm/glm.hpp>

class Camera : public GameObject {
public:
  void Init(float initDistance_ = 2.0f, float initAngleX_ = 0.0f,
            float initAngleY_ = 0.0f);

  void ResizeCameraViewport(int width_, int height_);
  void RotateCamera(float xRotation_, float yRotation_);
  void ZoomCamera(float distDelta_);

  glm::mat4 &GetProjectionMatrix() { return mProjection; }
  glm::mat4 &GetModelViewMatrix() { return mModelView; }

  bool Event(char event_, const void *data_);

private:
  void ComputeModelViewMatrix();
  float mAngleX, mAngleY, mDistance, mRangeDistanceCamera[2];
  glm::mat4 mProjection, mModelView;
};

#endif
