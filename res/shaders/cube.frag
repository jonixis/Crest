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

in vec3 v_position;
in vec3 v_normal;
in vec4 v_normalColor;

uniform vec3 u_color;
uniform PointLight u_pointLight;

void main()
{
  // Ambient
  vec3 ambientColor = u_pointLight.ambient * u_color;

  // Diffuse
  vec3 lightDir = normalize(u_pointLight.position - v_position);
  float diff = max(dot(v_normal, lightDir), 0.0);
  vec3 diffuseColor = u_pointLight.diffuse * diff * u_color;

  // Specular
  // TODO

  // Attenuation
  float distance = length(u_pointLight.position - v_position);
  float attenuation = 1.0 / (u_pointLight.constant + u_pointLight.linear * distance + u_pointLight.quadratic * distance * distance);
  ambientColor *= attenuation;
  diffuseColor *= attenuation;


  vec3 resultColor = ambientColor + diffuseColor;
  FragColor = vec4(resultColor, 1.0f);
}
