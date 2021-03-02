#include "DemoClearColor.h"
#include "Renderer.h"
#include "imgui.h"

namespace Demo {
  DemoClearColor::DemoClearColor() : m_clearColor{0.2f, 0.3f, 0.8f, 1.0f} {

  }

  DemoClearColor::~DemoClearColor() {

  }

  void DemoClearColor::onUpdate(float deltaTime) {

  }

  void DemoClearColor::onRender() {
    GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
  }

  void DemoClearColor::onImGuiRender() {
    ImGui::ColorEdit4("Clear Color", m_clearColor);
  }
}
