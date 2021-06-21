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

};
