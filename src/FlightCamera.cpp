#include <iostream>
#include "FlightCamera.h"

FlightCamera::FlightCamera(glm::uvec2 viewPortSize, glm::vec3 position, glm::vec3 target, glm::vec3 up) : Camera(
        viewPortSize, position, target, up) {
    // TODO find other solution
    m_pitch = glm::degrees(asin(-m_forward.z)) - 90.0f;
    m_yaw = glm::degrees(atan2(m_forward.y, m_forward.x));
}

void FlightCamera::update() {
    auto currentFrameTime = (float) glfwGetTime();
    m_deltaFrameTime = currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = currentFrameTime;

    const float cameraSpeed = 5.0f * m_deltaFrameTime;

    // Process keyboard input
    if (m_inputManager->isKeyPressed(GLFW_KEY_W)) {
        m_position += cameraSpeed * m_forward;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_S)) {
        m_position -= cameraSpeed * m_forward;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_A)) {
        m_position -= cameraSpeed * m_right;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_D)) {
        m_position += cameraSpeed * m_right;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_SPACE)) {
        m_position += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        m_position -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }

    if (m_inputManager->isCursorHidden()) {
        // Process mouse movement
        float sensitivity = 0.1f;
        glm::vec2 mouseDelta = m_inputManager->getMouseDelta();
        mouseDelta.x *= sensitivity;
        mouseDelta.y *= sensitivity;

        m_yaw += mouseDelta.x;
        m_pitch += mouseDelta.y;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 newForward;
        newForward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        newForward.y = sin(glm::radians(m_pitch));
        newForward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        // Update view vectors
        m_forward = glm::normalize(newForward);
        m_right = glm::normalize(glm::cross(m_forward, {0.0f, 1.0f, 0.0f}));
        m_up = glm::normalize(glm::cross(m_right, m_forward));
    }

    updateViewMatrix();
}

void FlightCamera::setInputManager(const std::shared_ptr<InputManager>& inputManager) {
    m_inputManager = inputManager;
}

