//
// Created by Jonathan Stahl on 21.06.21.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow *window) {
    m_window = window;
}

bool InputManager::isKeyPressed(int keycode) {
    auto state = glfwGetKey(m_window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}
