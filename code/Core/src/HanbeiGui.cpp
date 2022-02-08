#include "../headers/HanbeiGui.h"
#include <imgui.h>
#include <iostream>

HanbeiGui::HanbeiGui() {}

void HanbeiGui::DrawGui() const {
  ImGui::Begin("Options", 0, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("Render");
  ImGui::SliderInt("Point size", &mValue, 1, 7);
  ImGui::End();
}
