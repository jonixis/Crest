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

  if (!m_material)
    m_material = std::make_shared<Material>();
}

void Mesh::addVertex(const Vertex& vertex) {
  m_vertices.push_back(vertex);
}

void Mesh::addIndex(const unsigned int index) {
  m_indices.push_back(index);
}

void Mesh::setMaterial(const std::shared_ptr<Material> material) {
  m_material = material;
}

void Mesh::draw(std::shared_ptr<Shader> shader) const {
  if (!m_VAO || !m_IBO) {
    std::cout << "Initialize model before drawing!" << std::endl;
    exit(1);
  }

  shader->setUniform3f("u_material.ka", m_material->ka[0], m_material->ka[1], m_material->ka[2]);
  shader->setUniform3f("u_material.kd", m_material->kd[0], m_material->kd[1], m_material->kd[2]);
  shader->setUniform3f("u_material.ks", m_material->ks[0], m_material->ks[1], m_material->ks[2]);
  shader->setUniform1f("u_material.ns", m_material->ns);

  Renderer::draw(*m_VAO, *m_IBO, *shader);
}

unsigned int Mesh::getNumOfVertices() const {
  return m_vertices.size();
}
