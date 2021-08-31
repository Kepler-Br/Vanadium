#include "View.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <utility>

View::View(vanadium::Ref<Model> model) : _model(std::move(model)) {}

void View::draw() {
  if (ImGui::Begin("Fractal control", nullptr)) {
    ImGui::DragFloat2("Camera angle",
                      glm::value_ptr(this->_model->getCameraAngleRef()), 0.01f);
    ImGui::DragFloat("Camera radius", &this->_model->getRadiusRef(), 0.01f);
    ImGui::DragFloat("Iterations", &this->_model->getIterationsRef(), 1.0f,
                     1.00f, 50.0f);
    ImGui::DragFloat("Bailout", &this->_model->getBailoutRef(), 0.05f, 0.001f,
                     100.0f);
    ImGui::ColorEdit3("Aura color",
                      glm::value_ptr(this->_model->getAuraColorRef()),
                      ImGuiColorEditFlags_DisplayHSV);
  }
  ImGui::End();
}
