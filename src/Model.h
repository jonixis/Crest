#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

static const glm::mat4 identityMatrix{ 1.0f };

class Model {

 public:

  Model(const std::string& filepath);
  ~Model();

  void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, std::shared_ptr<Shader> shader) const;

  void setPosition(const glm::vec3& position);
  void setRotation(const glm::vec3& rotation);
  void setScale(const glm::vec3& scale);

  const glm::mat4 getModelMatrix() const { return m_modelMatrix; }
  const glm::mat4 getNormalMatrix() const { return m_normalMatrix; }

 private:

  glm::mat3 m_normalMatrix;

  glm::mat4 m_modelMatrix;
  glm::mat4 m_translationMatrix = glm::mat4(1.0f);
  glm::mat4 m_rotationMatrix = glm::mat4(1.0f);
  glm::mat4 m_scalingMatrix = glm::mat4(1.0f);

  glm::vec3 m_position;

  std::vector<std::shared_ptr<Mesh>> m_meshes;

  unsigned int m_numMissingNormals = 0;
  unsigned int m_numMissingTexCoords = 0;

  std::string m_filePath;

  void loadModel(const std::string& filepath);
  void addMesh(const std::shared_ptr<Mesh> mesh);
  void calculateModelMatrix();


};
