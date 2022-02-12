#include "../headers/Scene.h"

#include "../../Connector/headers/Context.h"
#include <GL/gl.h>
#include <backends/imgui_impl_glut.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

void Scene::Draw() const {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGLUT_NewFrame();
  DrawGui();
  // Rendering
  ImGui::Render();
  ImGuiIO &io = ImGui::GetIO();
  glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Scene::Event(char event_) {
  auto &UIdata = Context::GetActualContext().GetUIData();
  switch (event_) {
  case UIEvent::Key:
    if (UIdata.GetKeyPressed()) {
      ImGui_ImplGLUT_KeyboardFunc(UIdata.GetKey(), UIdata.GetMouseX(),
                                  UIdata.GetMouseY());
    } else {
      ImGui_ImplGLUT_KeyboardUpFunc(UIdata.GetKey(), UIdata.GetMouseX(),
                                    UIdata.GetMouseY());
    }
    if (ImGui::GetIO().WantCaptureKeyboard)
      return true;
    break;
  case UIEvent::SpecialKey:
    if (UIdata.GetSpecialKeyPressed()) {
      ImGui_ImplGLUT_SpecialFunc(UIdata.GetSpecialKey(), UIdata.GetMouseX(),
                                 UIdata.GetMouseY());
    } else {
      ImGui_ImplGLUT_SpecialUpFunc(UIdata.GetSpecialKey(), UIdata.GetMouseX(),
                                   UIdata.GetMouseY());
    }
    if (ImGui::GetIO().WantCaptureKeyboard)
      return true;
    break;
  case UIEvent::MouseMove:
    ImGui_ImplGLUT_MotionFunc(UIdata.GetMouseX(), UIdata.GetMouseY());
    if (ImGui::GetIO().WantCaptureMouse)
      return true;
    break;
  case UIEvent::MouseClick:
    ImGui_ImplGLUT_MouseFunc(UIdata.GetMouseButton(), UIdata.GetMouseState(),
                             UIdata.GetMouseX(), UIdata.GetMouseY());
    if (ImGui::GetIO().WantCaptureMouse)
      return true;
    break;
  case UIEvent::Resize:
    ImGui_ImplGLUT_ReshapeFunc(UIdata.GetWidth(), UIdata.GetHeight());
    break;
  }
  return false;
}
