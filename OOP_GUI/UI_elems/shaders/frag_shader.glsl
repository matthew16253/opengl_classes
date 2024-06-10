<<<<<<< HEAD
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D UniformTexture;
uniform vec4 UniformColor;

void main()
{
  FragColor = texture(UniformTexture,TexCoord) * UniformColor;
=======
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D UniformTexture;
uniform vec4 UniformColor;

void main()
{
  FragColor = texture(UniformTexture,TexCoord) * UniformColor;
>>>>>>> 09b7cc8 (reinit commit)
}