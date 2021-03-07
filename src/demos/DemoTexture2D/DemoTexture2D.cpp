#include "DemoTexture2D.h"

#include <memory>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

namespace Demo {
  DemoTexture2D::DemoTexture2D(const Settings& settings) : Demo(settings), m_proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_translation(0.0f, 0.0f, 0.0f) {

    float positions[] = {
      -0.5f, -0.5f, 0.0f, 0.0f, // index 0
      0.5f, -0.5f, 1.0f, 0.0f, // index 1
      0.5f, 0.5f, 1.0f, 1.0f, // index 2
      -0.5f, 0.5f, 0.0f, 1.0f // index 3
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2); // Add vertex positions
    layout.push<float>(2); // Add vertex texture coords
    m_VAO->addBuffer(*m_VBO, layout);
    m_IBO = std::make_unique<IndexBuffer>(indices, 6);

    m_shader = std::make_unique<Shader>("shaders/basic");
    m_shader->bind();
    m_shader->setUniform4f("u_color", 0.8f, 0.2f, 0.8f, 1.0f);

    m_texture = std::make_unique<Texture>("res/textures/logo.png");
    m_shader->setUniform1i("u_texture", 0);
  }

  DemoTexture2D::~DemoTexture2D() {

  }

  void DemoTexture2D::onUpdate(float deltaTime) {

  }

  void DemoTexture2D::onRender() {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    m_texture->bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
    glm::mat4 mvp = m_proj * m_view * model;

    // Usually one would use materials for this and pass material to renderer
    m_shader->bind();
    m_shader->setUniformMat4f("u_MVP", mvp);

    renderer.draw(*m_VAO, *m_IBO, *m_shader);
  }

  void DemoTexture2D::onImGuiRender() {
      ImGui::Text("Texture2D");
      ImGui::SliderFloat3("Translation", &m_translation.x, -2.0f, 2.0f);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}
