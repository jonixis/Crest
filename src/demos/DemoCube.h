#pragma once

#include "Camera.h"
#include "Demo.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include <memory>
#include "FlightCamera.h"

namespace Demo {
	class DemoCube : public Demo {
	public:
    DemoCube(const Settings& settings);
		~DemoCube();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Texture> m_texture;

    FlightCamera m_camera;

	};

}
