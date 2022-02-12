#include "../headers/Camera.h"
#define GLM_FORCE_RADIANS
#include <GL/freeglut.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define PI 3.14159f

void Camera::Init(float initDistance_, float initAngleX_, float initAngleY_) {
  mDistance = initDistance_;
  mAngleX = initAngleX_;
  mAngleY = initAngleY_;
  mRangeDistanceCamera[0] = initDistance_ < 0.1f ? initDistance_ : 0.1f;
  mRangeDistanceCamera[1] = initDistance_ > 3.0f ? initDistance_ : 3.0f;
  ComputeModelViewMatrix();
}

void Camera::ResizeCameraViewport(int width_, int height_) {
  mProjection = glm::perspective(60.f / 180.f * PI,
                                 float(width_) / float(height_), 0.01f, 100.0f);
}

void Camera::RotateCamera(float xRotation_, float yRotation_) {
  mAngleX += xRotation_;
  mAngleX = glm::max(-75.0f, glm::min(mAngleX, 75.0f));
  mAngleY += yRotation_;
  ComputeModelViewMatrix();
}

void Camera::ZoomCamera(float distDelta_) {
  mDistance += distDelta_;
  mDistance = glm::max(mRangeDistanceCamera[0],
                       glm::min(mDistance, mRangeDistanceCamera[1]));
  ComputeModelViewMatrix();
}

void Camera::ComputeModelViewMatrix() {
  mModelView = glm::mat4(1.0f);
  mModelView = glm::translate(mModelView, glm::vec3(0.0f, 0.0f, -mDistance));
  mModelView = glm::rotate(mModelView, mAngleX / 180.f * PI,
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mModelView = glm::rotate(mModelView, mAngleY / 180.f * PI,
                           glm::vec3(0.0f, 1.0f, 0.0f));
}

bool Camera::Event(char event_, const void *data_) {
  switch (event_) {
  case UIEvent::Resize: {
    const auto *data = static_cast<const UIData *>(data_);
    ResizeCameraViewport(data->width, data->height);
    break;
  }
  case UIEvent::MouseMove:
  case UIEvent::MouseClick: {
    const auto *data = static_cast<const UIData *>(data_);
    glm::ivec2 aux = mLastMouse;
    glm::ivec2 diff = glm::ivec2(data->mouseX - aux.x, data->mouseY - aux.y);
    if (data->mouseState == GLUT_DOWN) {
      mLastMouse = glm::ivec2(data->mouseX, data->mouseY);
    } else {
      mLastMouse = glm::ivec2(-1, -1);
    }
    if (aux.x != -1 && data->mouseState == GLUT_DOWN) {
      if (data->mouseButton == GLUT_LEFT_BUTTON) {
        RotateCamera(0.5f * (diff.y), 0.5f * (diff.x));
        return true;
      }
      if (data->mouseButton == GLUT_RIGHT_BUTTON) {
        ZoomCamera(0.01f * (diff.y));
        return true;
      }
    }
    break;
  }
  }
  return false;
}
