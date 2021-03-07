#include "DemoMenu.h"

#include <imgui.h>

namespace Demo {

  DemoMenu::DemoMenu(Demo*& currentDemo) : m_currentDemo(currentDemo) {

  }

  void DemoMenu::onImGuiRender() {
    for (auto& demo : m_demos) {
      if (ImGui::Button(demo.first.c_str()))
        m_currentDemo = demo.second();
    }

  }
}
