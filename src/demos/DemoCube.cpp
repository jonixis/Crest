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
      // front
      -1.0, -1.0,  1.0, 0.0, 0.0, 1.0,
      1.0, -1.0,  1.0, 0.0, 0.0, 1.0,
      1.0,  1.0,  1.0, 0.0, 0.0, 1.0,
      -1.0,  1.0,  1.0, 0.0, 0.0, 1.0,

      // top
      -1.0,  1.0,  1.0, 0.0, 1.0, 0.0,
      1.0,  1.0,  1.0, 0.0, 1.0, 0.0,
      1.0,  1.0, -1.0, 0.0, 1.0, 0.0,
      -1.0,  1.0, -1.0, 0.0, 1.0, 0.0,

      // back
      1.0, -1.0, -1.0, 0.0, 0.0, -1.0,
      -1.0, -1.0, -1.0, 0.0, 0.0, -1.0,
      -1.0,  1.0, -1.0, 0.0, 0.0, -1.0,
      1.0,  1.0, -1.0, 0.0, 0.0, -1.0,

      // bottom
      -1.0, -1.0, -1.0, 0.0, -1.0, 0.0,
      1.0, -1.0, -1.0, 0.0, -1.0, 0.0,
      1.0, -1.0,  1.0, 0.0, -1.0, 0.0,
      -1.0, -1.0,  1.0, 0.0, -1.0, 0.0,

      // left
      -1.0, -1.0, -1.0, -1.0, 0.0, 0.0,
      -1.0, -1.0,  1.0, -1.0, 0.0, 0.0,
      -1.0,  1.0,  1.0, -1.0, 0.0, 0.0,
      -1.0,  1.0, -1.0, -1.0, 0.0, 0.0,

      // right
      1.0, -1.0,  1.0, 1.0, 0.0, 0.0,
      1.0, -1.0, -1.0, 1.0, 0.0, 0.0,
      1.0,  1.0, -1.0, 1.0, 0.0, 0.0,
      1.0,  1.0,  1.0, 1.0, 0.0, 0.0,
    };

    unsigned int indices[] = {
      // front
      0,  1,  2,
      2,  3,  0,

      // top
      4,  5,  6,
      6,  7,  4,

      // back
      8,  9, 10,
      10, 11,  8,

      // bottom
      12, 13, 14,
      14, 15, 12,

      // left
      16, 17, 18,
      18, 19, 16,

      // right
      20, 21, 22,
      22, 23, 20,
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLCall(glEnable(GL_DEPTH_TEST));

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices, 24 * 6 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(3); // Add vertex positions
    layout.push<float>(3); // Add vertex normals
    m_VAO->addBuffer(*m_VBO, layout);
    m_IBO = std::make_unique<IndexBuffer>(indices, 36);

    m_shader = std::make_unique<Shader>("res/shaders/cube");
    m_shader->bind();
    m_shader->setUniform4f("u_color", 0.8f, 0.2f, 0.8f, 1.0f);

    m_camera = FlightCamera(m_settings.viewPortSize, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  }

  DemoCube::~DemoCube() {

  }

  void DemoCube::onUpdate(float deltaTime) {

  }

  void DemoCube::onRender() {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 viewMatrix = m_camera.getViewMatrix();
    glm::mat4 projectionMatrix = m_camera.getProjectionMatrix();

    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    m_shader->bind();
    m_shader->setUniformMat4f("u_MVP", mvp);

    m_renderer.draw(*m_VAO, *m_IBO, *m_shader);
  }

  void DemoCube::onImGuiRender() {
      ImGui::Text("DemoCube");
      ImGui::NewLine();
      ImGui::Text("Rotation");
      ImGui::SliderFloat("X - Axis", &m_rotationX, -360.0f, 360.0f);
      ImGui::SliderFloat("Y - Axis", &m_rotationY, -360.0f, 360.0f);
      ImGui::SliderFloat("Z - Axis", &m_rotationZ, -360.0f, 360.0f);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}
