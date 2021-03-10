#pragma once

#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class Mesh {

 public:

  Mesh() = default;
  Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
  ~Mesh();

  void init();
  void addVertex(const Vertex& vertex);
  void addIndex(const unsigned int index);
  void draw(std::shared_ptr<Shader> shader) const; // TODO add material

  unsigned int getNumOfVertices() const;

 private:

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<IndexBuffer> m_IBO;

  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;

};
