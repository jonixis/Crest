#pragma once

#include <glad/glad.h>
#include <csignal>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();                 \
  x;                                            \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {

 public:
  void clear() const;
  void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};
