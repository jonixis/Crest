//
// Created by Jonathan Stahl on 21.06.21.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow *window) {
    m_window = window;

    // Store pointer to this input manager instance in gflw window
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(m_window, mouseMovementCallback);
    glfwSetKeyCallback(m_window, keyCallback);

    setCursorHidden(false);
}

bool InputManager::isKeyPressed(int keycode) const {
    auto state = glfwGetKey(m_window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 InputManager::getMouseDelta() {
    glm::vec2 mouseDelta;
    mouseDelta.x = m_mouseCurrentX - m_mouseLastX;
    mouseDelta.y = m_mouseLastY - m_mouseCurrentY;

    m_mouseLastX = m_mouseCurrentX;
    m_mouseLastY = m_mouseCurrentY;

    return mouseDelta;
}

void InputManager::mouseMovementCallback(GLFWwindow* window, double xPos, double yPos) {
    auto inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

    inputManager->m_mouseCurrentX = static_cast<float>(xPos);
    inputManager->m_mouseCurrentY = static_cast<float>(yPos);
}

void InputManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_C && action == GLFW_RELEASE)
        inputManager->setCursorHidden(!inputManager->isCursorHidden());
}

void InputManager::setCursorHidden(bool hidden) {
    int cursorMode = hidden ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
    glfwSetInputMode(m_window, GLFW_CURSOR, cursorMode);

    // Reset position to prevent sudden jump
    double currentX, currentY;
    glfwGetCursorPos(m_window, &currentX, &currentY);
    m_mouseCurrentX = static_cast<float>(currentX);
    m_mouseCurrentY = static_cast<float>(currentY);
    m_mouseLastX = m_mouseCurrentX;
    m_mouseLastY = m_mouseCurrentY;
}

bool InputManager::isCursorHidden() const {
    int cursorMode = glfwGetInputMode(m_window, GLFW_CURSOR);
    return cursorMode == GLFW_CURSOR_DISABLED;
}

