#include "../headers/Application.h"

Application::Application() {}

bool Application::Event(char event) {
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
  return false;
}
bool Application::Update(int dt) { return !mExit; }

void Application::Draw() const {}
void Application::RenderGui() {}

void Application::Init() {}
bool Application::Load(int argc, char **argv) { return true; }
