#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "Renderer.h"

Shader::Shader(const std::string& filePath) : m_filePath(filePath), m_rendererID(0) {
  ShaderProgramSource source = parseShader(filePath);
  m_rendererID = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
  GLCall(glDeleteProgram(m_rendererID));
}

ShaderProgramSource Shader::parseShader(const std::string& filepath) {

  enum class ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string vertexFilePath = filepath + ".vert";
  std::string fragmentFilePath = filepath + ".frag";

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::VERTEX;

  for (auto& shader : ss) {

      std::ifstream stream = type == ShaderType::VERTEX
        ? std::ifstream(vertexFilePath)
        : std::ifstream(fragmentFilePath);

      while (getline(stream, line)) {
        shader << line << "\n";
      }

      type = ShaderType::FRAGMENT;
  }

  return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
  GLCall(unsigned int id = glCreateShader(type));
  const char* src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char* message = (char*)alloca(length * sizeof(char)); // Dynamically allocate space for char array on stack
    GLCall(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " shader!" << std::endl;
    std::cout << message << std::endl;
    GLCall(glDeleteShader(id));

    return 0;
  }

  return id;
}

unsigned int Shader::createShader(const std::string &vertexShader,
                                 const std::string &fragmentShader) {
  GLCall(unsigned int program = glCreateProgram());
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

void Shader::bind() const {
  GLCall(glUseProgram(m_rendererID));
}

void Shader::unbind() const {
  GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int value) {
  GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value) {
  GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
  GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat3f(const std::string& name, const glm::mat3& matrix) {
  GLCall(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
  GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string& name) {
  if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    return m_uniformLocationCache[name];

  GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));

  if (location == -1)
    std::cout << "Warning: Uniform '" << name <<"' doesn't exist!" << std::endl;

  m_uniformLocationCache[name] = location;
  return location;
}
