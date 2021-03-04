#pragma once

#include "glm/glm.hpp"

class Camera {
 public:
  Camera() = default;
	Camera(glm::uvec2 viewPortSize, glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	virtual ~Camera() {};

	virtual void update() = 0;

	const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
	const glm::mat4& getProjectionMatrix() const { return m_projecionMatrix; }

 private:

	glm::uvec2 m_viewPortSize;

	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_target;
	glm::vec3 m_up;
	glm::vec3 m_right;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projecionMatrix;

};
