#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Renderer.h"

Camera::Camera(glm::uvec2 viewPortSize,
               glm::vec3 position,
               glm::vec3 target,
               glm::vec3 up)
        : m_viewPortSize(viewPortSize),  m_position(position), m_target(target) {
    GLCall(glViewport(0, 0, m_viewPortSize.x, m_viewPortSize.y));

    m_forward = glm::normalize(m_target - m_position);
    m_right = glm::normalize(glm::cross(up, m_forward));
    m_up = glm::cross(m_forward, m_right);

    updateViewMatrix();

    float aspect = float(viewPortSize.x) / float(viewPortSize.y);
    m_projecionMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}

void Camera::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
}
