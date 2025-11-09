#include "control_widget.h"
#include "../vendor/glfw/src/internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ControlWidget::ControlWidget(GLFWwindow *_window, Spline *_spline)
    : window(_window), spline(_spline) {
  std::cout << "Initializing control widget..." << std::endl;
  Init();
}

ControlWidget::~ControlWidget() {
  std::cout << "Destroying control widget..." << std::endl;
  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

void ControlWidget::Init() const {
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void ControlWidget::Render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGuiWindowFlags flags =
  ImGuiWindowFlags_NoResize |
  ImGuiWindowFlags_AlwaysAutoResize |
  ImGuiWindowFlags_NoSavedSettings;

  ImGui::Begin("Controls", nullptr, flags);
  ImGui::Checkbox("Closed Loop", &spline->GetLoopFlag());
  if (ImGui::SliderFloat("Resolution", &spline->GetResolution(), 0.00005f, 0.00065f, "%.5f")) {
    spline->CalculateUnitsPerSample();
  }
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ControlWidget::WantToCaptureMouse() const {
  return ImGui::GetIO().WantCaptureMouse;
}