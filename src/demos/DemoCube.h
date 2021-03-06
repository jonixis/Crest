#pragma once

#include "Camera.h"
#include "Demo.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include <memory>
#include "FlightCamera.h"
#include "Renderer.h"

struct PointLight {
  glm::vec3 position;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  float constant;
  float linear;
  float quadratic;
};

struct Material {
  float shininess;
};

namespace Demo {
	class DemoCube : public Demo {
	public:

    DemoCube(const Settings& settings);
		~DemoCube();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:

    Renderer m_renderer;
    FlightCamera m_camera;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_shader;

    PointLight m_pointLight;
    Material m_material;

    float m_rotationX = 0.0f;
    float m_rotationY = 0.0f;
    float m_rotationZ = 0.0f;

	};

}
