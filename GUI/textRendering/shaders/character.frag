#version 330 core

uniform vec4 ourColor;
uniform sampler2D ourTexture;
in vec2 TexCoord;
out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0, 1.0, 1.0, texture(ourTexture,TexCoord).r) * ourColor;
}