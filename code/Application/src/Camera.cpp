#include "../headers/Camera.h"

#include "../../Connector/headers/Context.h"
#define GLM_FORCE_RADIANS
#include <GL/freeglut.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.14159f

void Camera::Init(float initDistance_, float initAngleX_, float initAngleY_) {
  mDistance = initDistance_;
  mAngleX = initAngleX_;
  mAngleY = initAngleY_;
  mPos = glm::vec3(0.0f, 0.0f, 0.0f);
  mVel = glm::vec3(0.0f);
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

void Camera::MoveCamera(glm::vec3 move_) {
  glm::mat4 auxDisp = glm::mat4(1.0f);
  auxDisp =
      glm::rotate(auxDisp, mAngleY / 180.f * PI, glm::vec3(0.0f, -1.0f, 0.0f));
  glm::vec4 aux = auxDisp * glm::vec4(move_, 1.0f);
  mPos += glm::vec3(aux / aux[3]);
  ComputeModelViewMatrix();
}

bool Camera::Update(int dt_) {
  MoveCamera(mVel * float(dt_));
  return true;
}

void Camera::ComputeModelViewMatrix() {
  mModelView = glm::mat4(1.0f);
  mModelView = glm::rotate(mModelView, mAngleX / 180.f * PI,
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mModelView = glm::rotate(mModelView, mAngleY / 180.f * PI,
                           glm::vec3(0.0f, 1.0f, 0.0f));
  mModelView =
      glm::translate(mModelView, mPos + glm::vec3(0.0f, 0.0f, -mDistance));
}

bool Camera::Event(char event_) {
  auto UIdata = Context::GetUIData();
  switch (event_) {
  case UIEvent::Key: {
    switch (UIdata.GetKey()) {
    case 'a':
      mVel.x += UIdata.GetKeyPressed() ? 0.001 : -0.001f;
      return true;
    case 's':
      mVel.z += UIdata.GetKeyPressed() ? -0.001 : 0.001f;
      return true;
    case 'd':
      mVel.x += UIdata.GetKeyPressed() ? -0.001 : 0.001f;
      return true;
    case 'w':
      mVel.z += UIdata.GetKeyPressed() ? 0.001 : -0.001f;
      return true;
    case ' ':
      mVel.y += UIdata.GetKeyPressed() ? -0.001 : 0.001f;
      return true;
    case 'z':
      mVel.y += UIdata.GetKeyPressed() ? 0.001 : -0.001f;
      return true;
    }
    break;
  }
  case UIEvent::Resize: {
    ResizeCameraViewport(UIdata.GetWidth(), UIdata.GetHeight());
    break;
  }
  case UIEvent::MouseMove:
  case UIEvent::MouseClick: {
    glm::ivec2 aux = mLastMouse;
    glm::ivec2 diff =
        glm::ivec2(UIdata.GetMouseX() - aux.x, UIdata.GetMouseY() - aux.y);
    if (UIdata.GetMouseState() == GLUT_DOWN) {
      mLastMouse = glm::ivec2(UIdata.GetMouseX(), UIdata.GetMouseY());
    } else {
      mLastMouse = glm::ivec2(-1, -1);
    }
    if (aux.x != -1 && UIdata.GetMouseState() == GLUT_DOWN) {
      if (UIdata.GetMouseButton() == GLUT_LEFT_BUTTON) {
        RotateCamera(0.5f * (diff.y), 0.5f * (diff.x));
        return true;
      }
      if (UIdata.GetMouseButton() == GLUT_RIGHT_BUTTON) {
        ZoomCamera(0.01f * (diff.y));
        return true;
      }
    }
    break;
  }
  }
  return false;
}
