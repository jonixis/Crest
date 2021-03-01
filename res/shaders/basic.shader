#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_MVP;

out vec2 v_texCoord;

void main()
{
  v_texCoord = texCoord;
  gl_Position = u_MVP * position;
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
  vec4 fragColor = u_color;
  vec4 texColor = texture(u_texture, v_texCoord);
  color = texColor * fragColor.r;
}
