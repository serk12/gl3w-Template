#include "../headers/Application.h"
#include "../headers/Camera.h"
#include "../headers/Model.h"
#include "../headers/Scene.h"
#include "../headers/ShaderProgram.h"
#include <iostream>

Application::Application() { mCamera = std::shared_ptr<Camera>(new Camera()); }

bool Application::Event(char event_) {
  switch (event_) {
  case UIEvent::Key:
    if (Context::GetActualContext().GetUIData().GetKey() == 27) { // esc
      mExit = true;
      return true;
    }
    break;
  default:
    break;
  }
  // context
  for (auto object : mObjects) {
    if (object->Event(event_))
      return true;
  }
  if (mScene->Event(event_))
    return true;
  if (mCamera->Event(event_))
    return true;
  return false;
}

bool Application::Update(int dt) {
  for (auto it = mObjects.begin(); it != mObjects.end();) {
    if ((*it)->Update(dt)) {
      it = mObjects.erase(it);
      continue;
    }
    ++it;
  }
  mScene->Update(dt);
  mCamera->Update(dt);
  return !mExit;
}

void Application::Draw() const {
  if (mShaders.size() > 0) {
    mShaders[0]->Use();
    mShaders[0]->SetCamera(mCamera);
    for (const auto &object : mObjects) {
      object->Draw();
    }
  }
  mScene->Draw();
  mCamera->Draw();
}

void Application::Init() { mCamera->Init(); }
