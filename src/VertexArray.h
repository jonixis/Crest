#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
  glm::vec2 tangent;
};

class VertexBufferLayout;


class VertexArray {

 public:

  VertexArray();
  ~VertexArray();

  void addBuffer(const VertexBuffer& vbo);
  void addCustomBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
  void bind() const;
  void unbind() const;

 private:

  unsigned int m_rendererID;

};
