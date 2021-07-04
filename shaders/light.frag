#version 410 core

layout(location = 0) out vec4 FragColor;

in vec3 v_position;
in vec3 v_normal;
in vec4 v_normalColor;

uniform vec3 u_color;

void main()
{

  vec3 resultColor = u_color;
  FragColor = vec4(resultColor, 1.0);
}
