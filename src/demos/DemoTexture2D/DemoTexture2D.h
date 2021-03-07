#pragma once

#include <glm/glm.hpp>

#include "Demo.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"

#include <memory>

namespace Demo {

  class DemoTexture2D : public Demo {

   public:

    DemoTexture2D(const Settings& settings);
    ~DemoTexture2D();

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

   private:

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Texture> m_texture;

    glm::mat4 m_proj, m_view;
    glm::vec3 m_translation;

  };

}
