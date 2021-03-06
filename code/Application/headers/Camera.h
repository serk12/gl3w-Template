#ifndef CAMERA_H
#define CAMERA_H

#include "../../Connector/headers/GameObject.h"

#include <glm/glm.hpp>

class Camera : public GameObject {
public:
  void Init(float initDistance_ = 0.5f, float initAngleX_ = 0.0f,
            float initAngleY_ = 0.0f);

  void ResizeCameraViewport(int width_, int height_);
  void RotateCamera(float xRotation_, float yRotation_);
  void ZoomCamera(float distDelta_);
  void MoveCamera(glm::vec3 move_);

  glm::mat4 &GetProjectionMatrix() { return mProjection; }
  glm::mat4 &GetModelViewMatrix() { return mModelView; }

  bool Update(int dt_) override;
  bool Event(char event_) override;

private:
  void ComputeModelViewMatrix();
  float mAngleX, mAngleY, mDistance, mRangeDistanceCamera[2];
  glm::mat4 mProjection, mModelView;
  glm::vec3 mPos;
  glm::vec3 mVel;
  glm::ivec2 mLastMouse = glm::ivec2(-1, -1);
};

#endif
