<<<<<<< HEAD
#version 330 core

layout (location=0) in vec2 inputPos;
layout (location=1) in vec2 textureCoord;


out vec2 TexCoord;

uniform mat4 UniformModel;
uniform mat4 UniformProjection;

void main()
{
  gl_Position = UniformProjection * UniformModel * vec4(inputPos, 0.0f, 1.0f);
  TexCoord = textureCoord;
=======
#version 330 core

layout (location=0) in vec2 inputPos;
layout (location=1) in vec2 textureCoord;


out vec2 TexCoord;

uniform mat4 UniformModel;
uniform mat4 UniformProjection;

void main()
{
  gl_Position = UniformProjection * UniformModel * vec4(inputPos, 0.0f, 1.0f);
  TexCoord = textureCoord;
>>>>>>> 09b7cc8 (reinit commit)
}