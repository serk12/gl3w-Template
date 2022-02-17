#include "../headers/AppGui.h"
#include <imgui.h>

AppGui::AppGui() {}

void AppGui::DrawGui() const {
  ImGui::Begin("Options", 0, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("Render");
  ImGui::SliderInt("Point size", &mValue, 1, 7);
  ImGui::End();
}
