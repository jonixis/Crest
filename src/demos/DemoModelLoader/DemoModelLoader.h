#pragma once

#include <memory>

#include "Camera.h"
#include "Demo.h"
#include "IndexBuffer.h"
#include "InputManager.h"
#include "Model.h"
#include "PointLight.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "FlightCamera.h"

namespace Demo {

    class DemoModelLoader : public Demo {

    public:

        DemoModelLoader(const Settings &settings, const std::shared_ptr<InputManager>& inputManager);

        ~DemoModelLoader();

        void onUpdate(float deltaTime) override;

        void onRender() override;

        void onImGuiRender() override;

    private:

        std::unique_ptr<FlightCamera> m_camera;

        std::shared_ptr<Shader> m_modelShader;
        std::shared_ptr<Shader> m_lightShader;

        std::unique_ptr<Model> m_sponzaModel;
        std::unique_ptr<Model> m_mandoModel;

        std::unique_ptr<PointLight> m_pointLight;

        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_mandoRotation = {0.0f, 0.0f, 0.0f};
        float m_scale = 1.0f;

        glm::vec3 m_pointLightPosition = {0.0f, 0.0f, 0.0f};

    };

}
