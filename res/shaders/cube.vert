#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_MVP;

out vec3 v_normal;
out vec4 v_normalColor;

void main()
{
  v_normal = normal;
  v_normalColor = vec4(normal * 0.5f + 0.5f, 1.0);
  gl_Position = u_MVP * position;
}
