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

  bool hasDiffuseTex;
  bool hasSpecularTex;
  bool hasNormalTex;

  sampler2D map_kd;
  sampler2D map_ks;
  sampler2D map_norm;
};


in vec2 v_texCoord;

in vec3 v_position;
in vec3 v_normal;

in vec4 v_normalColor;

uniform vec3 u_camPos;
uniform PointLight u_pointLight;
uniform Material u_material;

void main()
{
  // Ambient
  vec3 ambientMaterialColor = u_material.hasDiffuseTex ? texture(u_material.map_kd, v_texCoord).rgb : u_material.ka;
  vec3 ambientColor = u_pointLight.ambient * ambientMaterialColor;

  // Diffuse
  vec3 diffuseMaterialColor = u_material.hasDiffuseTex ? texture(u_material.map_kd, v_texCoord).rgb : u_material.kd;
  vec3 lightDir = normalize(u_pointLight.position - v_position);
  float diff = max(dot(v_normal, lightDir), 0.0);
  vec3 diffuseColor = u_pointLight.diffuse * diff * diffuseMaterialColor;

  // Specular
  vec3 specularMaterial = u_material.hasSpecularTex ? texture(u_material.map_ks, v_texCoord).rgb : u_material.ks;
  vec3 viewDir = normalize(u_camPos - v_position);
  // vec3 reflectDir = reflect(-lightDir, v_normal); // Phong
  // float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.ns); // Phong
  vec3 halfwayDir = normalize(lightDir + viewDir); // Blinn-Phong
  float spec = pow(max(dot(v_normal, halfwayDir), 0.0), u_material.ns); // Blinn-Phong
  vec3 specularColor = u_pointLight.specular * spec * specularMaterial;

  // Attenuation
  float distance = length(u_pointLight.position - v_position);
  float attenuation = 1.0 / (u_pointLight.constant + u_pointLight.linear * distance + u_pointLight.quadratic * distance * distance);
  ambientColor *= attenuation;
  diffuseColor *= attenuation;


  vec3 resultColor = ambientColor + diffuseColor + specularColor;
  FragColor = vec4(resultColor, 1.0);
}
