#include "DemoObjLoader.h"

#include <memory>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

namespace Demo {
  DemoObjLoader::DemoObjLoader(const Settings& settings) : Demo(settings) {


    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLCall(glEnable(GL_DEPTH_TEST));


    // m_model = std::make_unique<Model>("res/models/utah-teapot/utah-teapot.obj");
    // m_model = std::make_unique<Model>("res/models/newell_teaset/spoon.obj");
    // m_model = std::make_unique<Model>("res/models/newell_teaset/teacup.obj");
    // m_model = std::make_unique<Model>("res/models/newell_teaset/teapot.obj");
    m_model = std::make_unique<Model>("res/models/mandalorian/mando-helmet.obj");

    m_pointLight.position = glm::vec3(0.0f, -1.0f, 15.0f);

    m_pointLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    m_pointLight.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    m_pointLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    m_pointLight.constant = 1.0f;
    m_pointLight.linear = 0.045f;
    m_pointLight.quadratic = 0.0075f;

    m_material.shininess = 64.0f;
    m_material.color = glm::vec3(0.8f, 0.2f, 0.8f);

    m_shader = std::make_shared<Shader>("shaders/blinnPhong");

    m_camera = FlightCamera(m_settings.viewPortSize, {0.0f, 0.0f, 40.0f}, {0.0f, 0.0f, 0.0f});

  }

  DemoObjLoader::~DemoObjLoader() {

  }

  void DemoObjLoader::onUpdate(float deltaTime) {

    m_shader->bind();

    // Lighting
    m_shader->setUniform3f("u_pointLight.position", m_pointLight.position.x, m_pointLight.position.y, m_pointLight.position.z);
    m_shader->setUniform3f("u_pointLight.ambient", m_pointLight.ambient.x, m_pointLight.ambient.y, m_pointLight.ambient.z);
    m_shader->setUniform3f("u_pointLight.diffuse", m_pointLight.diffuse.x, m_pointLight.diffuse.y, m_pointLight.diffuse.z);
    m_shader->setUniform3f("u_pointLight.specular", m_pointLight.specular.x, m_pointLight.specular.y, m_pointLight.specular.z);
    m_shader->setUniform1f("u_pointLight.constant", m_pointLight.constant);
    m_shader->setUniform1f("u_pointLight.linear", m_pointLight.linear);
    m_shader->setUniform1f("u_pointLight.quadratic", m_pointLight.quadratic);

    // Camera
    m_shader->setUniform3f("u_camPos", m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);

    m_shader->unbind();

    // Transformations
    m_model->setPosition(m_position);
    m_model->setRotation(m_rotation);
    m_model->setScale({m_scale, m_scale, m_scale});

  }

  void DemoObjLoader::onRender() {
    m_model->draw(m_camera.getProjectionMatrix(), m_camera.getViewMatrix(), m_shader);
  }

  void DemoObjLoader::onImGuiRender() {
      ImGui::Text("DemoObjLoader");
      ImGui::NewLine();

      ImGui::Text("Transform");
      ImGui::SliderFloat3("Position", &m_position[0], -10.0f, 10.0f);
      ImGui::SliderFloat3("Rotation °", &m_rotation[0], -360.0f, 360.0f);
      ImGui::SliderFloat("Scale", &m_scale, 0.0f, 10.0f);

      ImGui::Text("Lighting");
      ImGui::SliderFloat3("Light - Position", &m_pointLight.position.x, -40.0f, 40.0f);

      // ImGui::Text("Material");
      // ImGui::SliderFloat("Shininess", &m_material.shininess, 1.0, 256);
      // ImGui::ColorEdit3("Color", &m_material.color.x);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}
