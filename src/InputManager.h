//
// Created by Jonathan Stahl on 21.06.21.
//
#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class InputManager {

public:
    InputManager(GLFWwindow* window);
    ~InputManager() = default;

    bool isKeyPressed(int keycode);

private:
    GLFWwindow* m_window;

};

