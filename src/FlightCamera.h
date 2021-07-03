#pragma once

#include "Camera.h"

#include "InputManager.h"

class FlightCamera : public Camera {

public:

    using Camera::Camera;

    void update() override;

    void setInputManager(const std::shared_ptr<InputManager>& inputManager);

private:
    std::shared_ptr<InputManager> m_inputManager;

    float m_deltaFrameTime = 0.0f;
    float m_lastFrameTime = 0.0f;

};
