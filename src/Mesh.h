#pragma once

#include <memory>
#include <vector>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

struct Material {
    float ns = 1.0f;
    glm::vec3 ka = {1.0f, 1.0f, 1.0f};
    glm::vec3 kd = {1.0f, 1.0f, 1.0f};
    glm::vec3 ks = {1.0f, 1.0f, 1.0f};

    std::shared_ptr<Texture> diffuseTexture = nullptr;
    std::shared_ptr<Texture> normalTexture = nullptr;
    std::shared_ptr<Texture> specularTexture = nullptr;
    // std::shared_ptr<Texture> metalnessTexture = nullptr;
    // std::shared_ptr<Texture> roughnessTexture = nullptr;
};

class Mesh {

public:

    Mesh() = default;

    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

    ~Mesh();

    void init();

    void addVertex(const Vertex &vertex);

    void addIndex(const unsigned int index);

    void setMaterial(const std::shared_ptr<Material> material);

    void draw(const std::shared_ptr<Shader>& shader, bool useMaterial) const;

    unsigned int getNumOfVertices() const;

private:

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;

    std::shared_ptr<Material> m_material;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

};
