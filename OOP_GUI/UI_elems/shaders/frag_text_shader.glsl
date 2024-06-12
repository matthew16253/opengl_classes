#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 UniformColor;
uniform sampler2D UniformTexture;

void main()
{
  FragColor = vec4(1.0, 1.0, 1.0, texture(UniformTexture,TexCoord).r) * UniformColor;
}