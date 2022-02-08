#include "../headers/Scene.h"
#include <GL/gl.h>
#include <backends/imgui_impl_glut.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

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

bool Scene::Event(char event_, const void *data_) {
  const auto *dataUI = static_cast<const UIData *>(data_);
  switch (event_) {
  case UIEvent::Key:
    if (dataUI->keyPressed) {
      ImGui_ImplGLUT_KeyboardFunc(dataUI->key, dataUI->mouseX, dataUI->mouseY);
    } else {
      ImGui_ImplGLUT_KeyboardUpFunc(dataUI->key, dataUI->mouseX,
                                    dataUI->mouseY);
    }
    if (ImGui::GetIO().WantCaptureKeyboard)
      return true;
    break;
  case UIEvent::SpecialKey:
    if (dataUI->specialKeyPressed) {
      ImGui_ImplGLUT_SpecialFunc(dataUI->specialKey, dataUI->mouseX,
                                 dataUI->mouseY);
    } else {
      ImGui_ImplGLUT_SpecialUpFunc(dataUI->specialKey, dataUI->mouseX,
                                   dataUI->mouseY);
    }
    if (ImGui::GetIO().WantCaptureKeyboard)
      return true;
    break;
  case UIEvent::MouseMove:
    ImGui_ImplGLUT_MotionFunc(dataUI->mouseX, dataUI->mouseY);
    if (ImGui::GetIO().WantCaptureMouse)
      return true;
    break;
  case UIEvent::MouseClick:
    ImGui_ImplGLUT_MouseFunc(dataUI->mouseButton, dataUI->mouseState,
                             dataUI->mouseX, dataUI->mouseY);
    if (ImGui::GetIO().WantCaptureMouse)
      return true;
    break;
  case UIEvent::Resize:
    ImGui_ImplGLUT_ReshapeFunc(dataUI->width, dataUI->height);
    break;
  }
  return false;
}
