#include "DemoModelLoader.h"

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
  DemoModelLoader::DemoModelLoader(const Settings& settings) : Demo(settings) {


    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLCall(glEnable(GL_DEPTH_TEST));

    // m_model = std::make_unique<Model>("res/models/utah-teapot/utah-teapot.obj");
    // m_model = std::make_unique<Model>("res/models/newell_teaset/spoon.obj");
    // m_model = std::make_unique<Model>("res/models/newell_teaset/teacup.obj");
    // m_model = std::make_unique<Model>("res/models/newell_teaset/teapot.obj");
    // m_model = std::make_unique<Model>("res/models/mandalorian/mando-helmet.obj");
    // m_model = std::make_unique<Model>("res/models/sphere/sphere.obj");

    m_model = std::make_unique<Model>("res/models/sponza/sponza.obj", "res/models/sponza/");
    m_scale = 0.03f;
    m_rotation = {0.0f, 90.0f, 0.0f};


    m_pointLight = std::make_unique<PointLight>();
    m_pointLightPosition = {0.0f, 9.0f, 7.0f};
    m_pointLight->setPosition(m_pointLightPosition);

    m_modelShader = std::make_shared<Shader>("shaders/blinnPhong");
    m_lightShader = std::make_shared<Shader>("shaders/light");

    m_camera = FlightCamera(m_settings.viewPortSize, {3.0f, 20.0f, 35.0f}, {0.0f, 0.0f, 0.0f});

  }

  DemoModelLoader::~DemoModelLoader() {

  }

  void DemoModelLoader::onUpdate(float deltaTime) {

    // Transformations
    m_model->setPosition(m_position);
    m_model->setRotation(m_rotation);
    m_model->setScale({m_scale, m_scale, m_scale});

    m_pointLight->setPosition(m_pointLightPosition);


  }

  void DemoModelLoader::onRender() {

    /* Set uniforms */
    m_modelShader->bind();

    // Lighting
    m_modelShader->setUniform3f("u_pointLight.position", m_pointLight->getPosition());
    m_modelShader->setUniform3f("u_pointLight.ambient", m_pointLight->getAmbient());
    m_modelShader->setUniform3f("u_pointLight.diffuse", m_pointLight->getDiffuse());
    m_modelShader->setUniform3f("u_pointLight.specular", m_pointLight->getSpecular());
    m_modelShader->setUniform1f("u_pointLight.constant", m_pointLight->getAttConstant());
    m_modelShader->setUniform1f("u_pointLight.linear", m_pointLight->getAttLinear());
    m_modelShader->setUniform1f("u_pointLight.quadratic", m_pointLight->getAttQuadratic());

    // Camera
    m_modelShader->setUniform3f("u_camPos", m_camera.getPosition());

    m_modelShader->unbind();

    /* Draw models */
    m_model->draw(m_camera.getProjectionMatrix(), m_camera.getViewMatrix(), m_modelShader);
    m_pointLight->drawModel(m_camera.getProjectionMatrix(), m_camera.getViewMatrix(), m_lightShader);
  }

  void DemoModelLoader::onImGuiRender() {
      ImGui::Text("Demo Model Loader");
      ImGui::NewLine();

      ImGui::Text("Transform");
      ImGui::SliderFloat3("Position", &m_position[0], -10.0f, 10.0f);
      ImGui::SliderFloat3("° Rotation", &m_rotation[0], -360.0f, 360.0f);
      ImGui::SliderFloat("Scale", &m_scale, 0.0f, 10.0f);

      ImGui::Text("Lighting");
      ImGui::SliderFloat3("Point light - Position", &m_pointLightPosition.x, -40.0f, 40.0f);

      // ImGui::Text("Material");
      // ImGui::SliderFloat("Shininess", &m_material.shininess, 1.0, 256);
      // ImGui::ColorEdit3("Color", &m_material.color.x);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}
