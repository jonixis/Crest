#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include <cstddef>

VertexArray::VertexArray() {
  GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray() {
  GLCall(glDeleteVertexArrays(1, &m_rendererID));
}


void VertexArray::addBuffer(const VertexBuffer& vbo) {
  bind();
  vbo.bind();

  // Vertex positions
  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0));

  // Vertex normals
  GLCall(glEnableVertexAttribArray(1));
  GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal)));

  // Vertex texCoords
  GLCall(glEnableVertexAttribArray(2));
  GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords)));

  // Vertex tangents
  GLCall(glEnableVertexAttribArray(3));
  GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tangent)));
}

void VertexArray::addCustomBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) {
  bind();
  vbo.bind();
  const auto& elements = layout.getElements();
  uintptr_t offset = 0;
  for (unsigned int i = 0; i < elements.size(); ++i) {
    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
    offset += element.count * VertexBufferElement::getSizeOfType(element.type);
  }
}

void VertexArray::bind() const {
  GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const {
  GLCall(glBindVertexArray(0));
}
