#include "PointLight.h"
#include <memory>

PointLight::PointLight(const std::string &modelFilePath) {
    m_model = std::make_unique<Model>(modelFilePath);
//    m_model->setScale({0.5f, 0.5f, 0.5f});
}

PointLight::~PointLight() {

}

void PointLight::setPosition(const glm::vec3 &position) {
    m_position = position;
    m_model->setPosition(position);
}

void PointLight::setAmbient(const glm::vec3 &ambient) {
    m_ambient = ambient;
}

void PointLight::setDiffuse(const glm::vec3 &diffuse) {
    m_diffuse = diffuse;
}

void PointLight::setSpecular(const glm::vec3 &specular) {
    m_specular = specular;
}

void PointLight::setAttConstant(const float attConstant) {
    m_attConstant = attConstant;
}

void PointLight::setAttLinear(const float attLinear) {
    m_attLinear = attLinear;
}

void PointLight::setAttQuadratic(const float attQuadratics) {
    m_attQuadratic = attQuadratics;
}

void PointLight::drawModel(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
                           const std::shared_ptr<Shader>& shader) const {
    shader->bind();
    shader->setUniform3f("u_color", m_diffuse);

    m_model->draw(projectionMatrix, viewMatrix, shader, false);
}
