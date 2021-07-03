//
// Created by Jonathan Stahl on 21.06.21.
//
#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class InputManager {

public:
    InputManager(GLFWwindow* window);
    ~InputManager() = default;

    bool isCursorHidden() const;
    void setCursorHidden(bool hidden);

    bool isKeyPressed(int keycode) const;

    glm::vec2 getMouseDelta();

    static void mouseMovementCallback(GLFWwindow* window, double xPos, double yPos);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
    GLFWwindow* m_window;

    float m_mouseLastX = 0.0f;
    float m_mouseLastY = 0.0f;

    float m_mouseCurrentX = 0.0f;
    float m_mouseCurrentY = 0.0f;

};

