#pragma once

#include "Camera.h"
#include "InputManager.h"

class FlightCamera : public Camera {

public:

    FlightCamera() = default;

    FlightCamera(glm::uvec2 viewPortSize,
                 glm::vec3 position,
                 glm::vec3 target,
                 glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    void update(float deltaTime) override;

    void setInputManager(const std::shared_ptr<InputManager>& inputManager);

private:
    std::shared_ptr<InputManager> m_inputManager;

    float m_pitch = 0.0f;
    float m_yaw = 0.0f;
};
