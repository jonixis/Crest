#include "DemoCube.h"

#include <memory>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

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
    m_VAO->addCustomBuffer(*m_VBO, layout);
    m_IBO = std::make_unique<IndexBuffer>(indices, 36);

    m_pointLight.position = glm::vec3(0.0f, 3.0f, 1.0f);

    m_pointLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    m_pointLight.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    m_pointLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    m_pointLight.constant = 1.0f;
    m_pointLight.linear = 0.045f;
    m_pointLight.quadratic = 0.0075f;

    m_material.shininess = 64.0f;
    m_material.color = glm::vec3(0.8f, 0.2f, 0.8f);

    m_shader = std::make_unique<Shader>("shaders/cube");

    m_camera = FlightCamera(m_settings.viewPortSize, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    m_rotationX = 30.0f;
    m_rotationY = 45.0f;
  }

  DemoCube::~DemoCube() {

  }

  void DemoCube::onUpdate(float deltaTime) {

  }

  void DemoCube::onRender() {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 viewMatrix = m_camera.getViewMatrix();
    glm::mat4 projectionMatrix = m_camera.getProjectionMatrix();

    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    // Transformations
    m_shader->bind();
    m_shader->setUniformMat4f("u_modelMatrix", modelMatrix);
    m_shader->setUniformMat4f("u_mvpMatrix", mvp);

    // Lighting
    m_shader->setUniform3f("u_pointLight.position", m_pointLight.position.x, m_pointLight.position.y, m_pointLight.position.z);
    m_shader->setUniform3f("u_pointLight.ambient", m_pointLight.ambient.x, m_pointLight.ambient.y, m_pointLight.ambient.z);
    m_shader->setUniform3f("u_pointLight.diffuse", m_pointLight.diffuse.x, m_pointLight.diffuse.y, m_pointLight.diffuse.z);
    m_shader->setUniform3f("u_pointLight.specular", m_pointLight.specular.x, m_pointLight.specular.y, m_pointLight.specular.z);
    m_shader->setUniform1f("u_pointLight.constant", m_pointLight.constant);
    m_shader->setUniform1f("u_pointLight.linear", m_pointLight.linear);
    m_shader->setUniform1f("u_pointLight.quadratic", m_pointLight.quadratic);

    // Material
    m_shader->setUniform3f("u_color", m_material.color.x, m_material.color.y, m_material.color.z);
    m_shader->setUniform1f("u_material.shininess", m_material.shininess);

    // Camera
    m_shader->setUniform3f("u_camPos", m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);


    Renderer::draw(*m_VAO, *m_IBO, *m_shader);
  }

  void DemoCube::onImGuiRender() {
      ImGui::Text("DemoCube");
      ImGui::NewLine();

      ImGui::Text("Cube - Rotation");
      ImGui::SliderFloat("X - Axis", &m_rotationX, -360.0f, 360.0f);
      ImGui::SliderFloat("Y - Axis", &m_rotationY, -360.0f, 360.0f);
      ImGui::SliderFloat("Z - Axis", &m_rotationZ, -360.0f, 360.0f);

      ImGui::Text("Lighting");
      ImGui::SliderFloat3("Position", &m_pointLight.position.x, -10.0f, 10.0f);

      ImGui::Text("Material");
      ImGui::SliderFloat("Shininess", &m_material.shininess, 1.0, 256);
      ImGui::ColorEdit3("Color", &m_material.color.x);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}
