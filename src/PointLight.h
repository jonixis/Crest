#pragma once

#include "Model.h"
#include <memory>

class PointLight {

public:

    PointLight(const std::string &modelFilepath = "res/models/cube/cube.obj");

    ~PointLight();

    void setPosition(const glm::vec3 &position);

    void setAmbient(const glm::vec3 &ambient);

    void setDiffuse(const glm::vec3 &diffuse);

    void setSpecular(const glm::vec3 &specular);

    void setAttConstant(const float attConstant);

    void setAttLinear(const float attLinear);

    void setAttQuadratic(const float attQuadratics);

    const glm::vec3 &getPosition() const { return m_position; }

    const glm::vec3 &getAmbient() const { return m_ambient; }

    const glm::vec3 &getDiffuse() const { return m_diffuse; }

    const glm::vec3 &getSpecular() const { return m_specular; }

    const float getAttConstant() const { return m_attConstant; }

    const float getAttLinear() const { return m_attLinear; }

    const float getAttQuadratic() const { return m_attQuadratic; }


    void
    drawModel(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix, const std::shared_ptr<Shader>& shader) const;

private:

    // Colors
    glm::vec3 m_ambient = {0.1f, 0.1f, 0.1f};
    glm::vec3 m_diffuse = {0.9f, 0.9f, 0.9f};
    glm::vec3 m_specular = {1.0f, 1.0f, 1.0f};

    // Attenuation values
    float m_attConstant = 1.0f;
    float m_attLinear = 0.045f;
    float m_attQuadratic = 0.0075f;

    glm::vec3 m_position;

    std::unique_ptr<Model> m_model;

};
