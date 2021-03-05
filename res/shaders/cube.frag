#version 410 core

layout(location = 0) out vec4 color;

in vec3 v_normal;
in vec4 v_normalColor;

uniform vec4 u_color;

void main()
{
  vec4 fragColor = u_color;
  color = v_normalColor;
}
