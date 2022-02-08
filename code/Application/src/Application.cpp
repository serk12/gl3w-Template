#include "../headers/Application.h"

Application::Application() {}

bool Application::Event(char event, const void *data_ = nullptr) {
  switch (event) {
  case UIEvent::Key:
    if (GetKey() == 27) { // esc
      mExit = true;
      return true;
    }
    break;
  default:
    break;
  }
  // context
  const auto data = GetUIData();
  if (mScene->Event(event, data))
    return true;
  for (auto *object : mObjects) {
    if (object->Event(event))
      return true;
  }
  if (mCamera.Event(event, data))
    return true;
  return false;
}

bool Application::Update(int dt) {
  mScene->Update(dt);
  for (auto it = mObjects.begin(); it != mObjects.end();) {
    if (!(*it)->Update(dt)) {
      delete (*it);
      it = mObjects.erase(it);
      continue;
    }
    ++it;
  }
  mCamera.Update(dt);
  return !mExit;
}

void Application::Draw() const {
  mScene->Draw();
  for (auto &object : mObjects) {
    object->Draw();
  }
  mCamera.Draw();
}

void Application::Init() { mCamera.Init(); }
