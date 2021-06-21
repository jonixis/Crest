#include <iostream>
#include "FlightCamera.h"

void FlightCamera::update() {
    const float cameraSpeed = 0.2f;
    if (m_inputManager->isKeyPressed(GLFW_KEY_W)) {
        m_position += cameraSpeed * m_forward;
        updateViewMatrix();
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_S)) {
        m_position -= cameraSpeed * m_forward;
        updateViewMatrix();
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_A)) {
        m_position -= cameraSpeed * glm::normalize(glm::cross(m_forward, m_up));
        updateViewMatrix();
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_D)) {
        m_position += cameraSpeed * glm::normalize(glm::cross(m_forward, m_up));
        updateViewMatrix();
    }



}

void FlightCamera::setInputManager(const std::shared_ptr<InputManager> &inputManager) {
    m_inputManager = inputManager;
}
