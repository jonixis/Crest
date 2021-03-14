#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {

 public:

  Shader(const std::string& filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform1i(const std::string& name, int value);
  void setUniform1f(const std::string& name, float value);
  void setUniform3f(const std::string& name, const glm::vec3& vector3f);
  void setUniform4f(const std::string& name, const glm::vec4& vector4f);
  void setUniformMat3f(const std::string& name, const glm::mat3& matrix);
  void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

 private:

  ShaderProgramSource parseShader(const std::string& filepath);
  unsigned int compileShader(unsigned int type, const std::string& source);
  unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
  int getUniformLocation(const std::string& name);

 private:

  std::string m_filePath;
  unsigned int m_rendererID;
  std::unordered_map<std::string, int> m_uniformLocationCache;

};
