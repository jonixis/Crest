#version 410 core

layout(location = 0) out vec4 FragColor;

struct PointLight {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};

struct Material {
  vec3 ka;
  vec3 kd;
  vec3 ks;
  float ns;
};

in vec3 v_position;
in vec3 v_normal;
in vec4 v_normalColor;

uniform vec3 u_camPos;
uniform PointLight u_pointLight;
uniform Material u_material;

void main()
{

  vec3 resultColor = vec3(1.0, 1.0, 1.0);
  FragColor = vec4(resultColor, 1.0);
}
