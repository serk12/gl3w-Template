#ifndef CAMERA_H
#define CAMERA_H

#include "../../headers/GameObject.h"

class Camera : public GameObject {
public:
  void resizeCameraViewport(int width, int height);
};

#endif
