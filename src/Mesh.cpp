#include "Mesh.h"

#include <iostream>
#include <memory>

#include "Renderer.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) : m_vertices(vertices), m_indices(indices) {
  init();
}

Mesh::~Mesh() {

}


void Mesh::init() {
  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(m_vertices.data(), m_vertices.size() * sizeof(Vertex));

  m_VAO->addBuffer(*m_VBO);

  m_IBO = std::make_unique<IndexBuffer>(m_indices.data(), m_indices.size());
}

void Mesh::addVertex(const Vertex& vertex) {
  m_vertices.push_back(vertex);
}

void Mesh::addIndex(const unsigned int index) {
  m_indices.push_back(index);
}

void Mesh::draw(std::shared_ptr<Shader> shader) const {
  if (!m_VAO || !m_IBO) {
    std::cout << "Initialize model before drawing!" << std::endl;
    exit(1);
  }

  Renderer::draw(*m_VAO, *m_IBO, *shader);
}

unsigned int Mesh::getNumOfVertices() const {
  return m_vertices.size();
}
