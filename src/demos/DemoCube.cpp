#include "DemoCube.h"
#include "GLFW/glfw3.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBufferLayout.h"
#include <memory>

namespace Demo {
  DemoCube::DemoCube(const Settings& settings) : Demo(settings) {

    float vertices[] = {
      -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    };


    unsigned int indices[] =
      {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
      };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices, 8 * 5 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(3); // Add vertex positions
    layout.push<float>(2); // Add vertex texture coords
    m_VAO->addBuffer(*m_VBO, layout);
    m_IBO = std::make_unique<IndexBuffer>(indices, 36);

    m_shader = std::make_unique<Shader>("res/shaders/basic.shader");
    m_shader->bind();
    m_shader->setUniform4f("u_color", 0.8f, 0.2f, 0.8f, 1.0f);

    m_texture = std::make_unique<Texture>("res/textures/logo.png");
    m_shader->setUniform1i("u_texture", 0);

    m_camera = FlightCamera(m_settings.viewPortSize, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  }

  DemoCube::~DemoCube() {

  }

  void DemoCube::onUpdate(float deltaTime) {

  }

  void DemoCube::onRender() {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    m_texture->bind();

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 viewMatrix = m_camera.getViewMatrix();
    glm::mat4 projectionMatrix = m_camera.getProjectionMatrix();

    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    // Usually one would use materials for this and pass material to renderer
    m_shader->bind();
    m_shader->setUniformMat4f("u_MVP", mvp);

    renderer.draw(*m_VAO, *m_IBO, *m_shader);
  }

  void DemoCube::onImGuiRender() {
      ImGui::Text("DemoCube");
      // ImGui::SliderFloat3("Translation", &m_translation.x, -2.0f, 2.0f);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}
