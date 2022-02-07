#include "../headers/Camera.h"

void Camera::resizeCameraViewport(int width, int height) {
  mProjection = glm::perspective(60.f / 180.f * PI,
                                 float(width) / float(height), 0.01f, 100.0f);
}
