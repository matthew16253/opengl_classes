#version 330 core

layout (location=0) in vec2 inputPos;
layout (location=1) in vec2 textureCoord;

out vec2 TexCoord;

uniform mat4 UniformProjection;
uniform mat4 UniformModel;

void main()
{
  gl_Position = UniformProjection * UniformModel * vec4(inputPos,0,1);
  TexCoord = textureCoord;
}