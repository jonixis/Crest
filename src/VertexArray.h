#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;


class VertexArray {

 public:

  VertexArray();
  ~VertexArray();

  void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
  void bind() const;
  void unbind() const;

 private:

  unsigned int m_rendererID;

};
