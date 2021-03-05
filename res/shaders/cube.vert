#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_modelMatrix;
uniform mat4 u_MVP;

out vec3 v_position;
out vec3 v_normal;
out vec4 v_normalColor;

void main()
{
  v_position = vec3(u_modelMatrix * position);
  v_normal = mat3(transpose(inverse(u_modelMatrix))) * normal; // Calculate normalMatrix on CPU!
  v_normalColor = vec4(normal * 0.5f + 0.5f, 1.0f);

  gl_Position = u_MVP * position;
}
