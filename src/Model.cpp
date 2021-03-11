#include "Model.h"

#include <cstddef>
#include <memory>
#include <string>
#include <tiny_obj_loader.h>
#include <iostream>
#include <unordered_map>
#include <glm/ext/matrix_transform.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "glm/trigonometric.hpp"

Model::Model(const std::string& filepath) : m_filePath(filepath) {
  loadModel(filepath);
  calculateModelMatrix();
}

Model::~Model() {

}

void Model::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, std::shared_ptr<Shader> shader, bool useMaterial) const {
  //TODO only update matrices if changed
  glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * m_modelMatrix;

  shader->bind();
  shader->setUniformMat4f("u_modelMatrix", m_modelMatrix);
  shader->setUniformMat3f("u_normalMatrix", m_normalMatrix);
  shader->setUniformMat4f("u_mvpMatrix", mvpMatrix);

  for (const auto& mesh : m_meshes) {
    mesh->draw(shader, useMaterial);
  }
}

void Model::setPosition(const glm::vec3& position) {
  m_position = position;
  m_translationMatrix = glm::translate(identityMatrix, m_position);
  calculateModelMatrix();
}

void Model::setRotation(const glm::vec3& rotation) {

  m_rotationMatrix = glm::rotate(identityMatrix, glm::radians(rotation.x), {1.0f, 0.0f, 0.0f})
    * glm::rotate(identityMatrix, glm::radians(rotation.y), {0.0f, 1.0f, 0.0f})
    * glm::rotate(identityMatrix, glm::radians(rotation.z), {0.0f, 0.0f, 1.0f});

  calculateModelMatrix();
}

void Model::setScale(const glm::vec3& scale) {
  m_scalingMatrix = glm::scale(identityMatrix, scale);
  calculateModelMatrix();
}

void Model::loadModel(const std::string &filepath) {
  tinyobj::ObjReaderConfig readerConfig;
  readerConfig.mtl_search_path = "";

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(filepath, readerConfig)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
  }

  const tinyobj::attrib_t& attrib = reader.GetAttrib();
  const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();
  const std::vector<tinyobj::material_t>& materials = reader.GetMaterials();

  // Loop over shapes (mesh)
  for (size_t s = 0; s < shapes.size(); ++s) {
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

    // Use string encoded indices as key in index map
    // TODO Maybe implement own hash strategy for better performance?
    std::unordered_map<std::string, unsigned int> indexMap;

    // Set material of first face
    int materialId = shapes[s].mesh.material_ids[0];

    // Loop over faces
    size_t indexOffset = 0; // Depends on num of vertices per face
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
      int fv = shapes[s].mesh.num_face_vertices[f];

      // Loop over vertices in face
      for (size_t v = 0; v < fv; ++v) {
        tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];

        // Check if vertex already exists
        std::string indicesString = std::to_string(idx.vertex_index)
          + std::to_string(idx.normal_index)
          + std::to_string(idx.texcoord_index);

        auto it = indexMap.find(indicesString);
        if (it != indexMap.end()) {
          // Vertex already exists
          unsigned int vertexIndex = it->second;
          mesh->addIndex(vertexIndex);
          continue;
        }

        Vertex vertex;
        vertex.position.x = attrib.vertices[3 * idx.vertex_index + 0];
        vertex.position.y = attrib.vertices[3 * idx.vertex_index + 1];
        vertex.position.z = attrib.vertices[3 * idx.vertex_index + 2];

        if (idx.normal_index != -1) {
          vertex.normal.x = attrib.normals[3 * idx.normal_index + 0];
          vertex.normal.y = attrib.normals[3 * idx.normal_index + 1];
          vertex.normal.z = attrib.normals[3 * idx.normal_index + 2];
        } else {
          m_numMissingNormals += 1;
        }

        if (idx.texcoord_index != -1) {
          vertex.texCoords.x = attrib.texcoords[2 * idx.texcoord_index + 0];
          vertex.texCoords.y = attrib.texcoords[2 * idx.texcoord_index + 1];
        } else {
          m_numMissingTexCoords += 1;
        }

        unsigned int vertexIndex = mesh->getNumOfVertices();
        mesh->addIndex(vertexIndex);
        indexMap.insert({ indicesString, vertexIndex });

        mesh->addVertex(vertex);
      }

      indexOffset += fv;


      if (materialId != shapes[s].mesh.material_ids[f])
        materialId = -1; // Not all faces in mesh have same material -> reset
    }

    if (materialId != -1) {
      std::shared_ptr<Material> material = std::make_shared<Material>();
      material->ka = glm::vec3(
                               materials[materialId].ambient[0],
                               materials[materialId].ambient[1],
                               materials[materialId].ambient[2]);
      material->kd = glm::vec3(
                               materials[materialId].diffuse[0],
                               materials[materialId].diffuse[1],
                               materials[materialId].diffuse[2]);
      material->ks = glm::vec3(
                               materials[materialId].specular[0],
                               materials[materialId].specular[1],
                               materials[materialId].specular[2]);

      material->ns = materials[materialId].shininess;

      mesh->setMaterial(material);
      std::cout << "Added material to mesh: " << materials[materialId].name << std::endl;
    }

    addMesh(mesh);
  }

  std::cout << "[Model '" << m_filePath << "' loaded]" << std::endl;
  std::cout << "Number of meshes: " << m_meshes.size() << std::endl;
  if (m_numMissingNormals > 0)
    std::cout << "Number of missing normals: " << m_numMissingNormals << std::endl;
  if (m_numMissingTexCoords > 0)
    std::cout << "Number of missing texture coordinates: " << m_numMissingTexCoords << std::endl;
}

void Model::addMesh(const std::shared_ptr<Mesh> mesh) {
  mesh->init();
  m_meshes.push_back(mesh);
}

void Model::calculateModelMatrix() {
  m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scalingMatrix;
  m_normalMatrix = glm::transpose(glm::inverse(glm::mat3{ m_modelMatrix }));
}
