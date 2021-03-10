#pragma once

#include <memory>

#include "Camera.h"
#include "Demo.h"
#include "IndexBuffer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "FlightCamera.h"

#include "DemoCube.h" // TODO workaround because of pointlight and material redefiniton

namespace Demo {

  class DemoObjLoader : public Demo {

   public:

    DemoObjLoader(const Settings& settings);
    ~DemoObjLoader();

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

   private:

    FlightCamera m_camera;

    std::shared_ptr<Shader> m_shader;
    std::unique_ptr<Model> m_model;

    PointLight m_pointLight;
    DemoMaterial m_material;

    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};
    float m_scale = 1.0f;

  };

}
