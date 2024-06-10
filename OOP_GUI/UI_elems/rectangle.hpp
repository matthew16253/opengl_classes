<<<<<<< HEAD
#ifndef PLAIN_RECTANGLE_HPP
#define PLAIN_RECTANGLE_HPP

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include"../fd_decs.hpp"



namespace myui
{
  Rectangle::Rectangle(Display* creator, glm::vec2 _topleft, glm::vec2 _bottomright,
  Texture2D* _texture, const glm::vec4& _color, bool _shouldRender)
   : texture(_texture), color(_color), shouldRender(_shouldRender),
    Area(creator,_topleft,_bottomright)
  {
    creator->rectangles.push_back(this);
  }
}

=======
#ifndef PLAIN_RECTANGLE_HPP
#define PLAIN_RECTANGLE_HPP

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include"../fd_decs.hpp"



namespace myui
{
  Rectangle::Rectangle(Display* creator, glm::vec2 _topleft, glm::vec2 _bottomright,
  Texture2D* _texture, const glm::vec4& _color, bool _shouldRender)
   : texture(_texture), color(_color), shouldRender(_shouldRender),
    Area(creator,_topleft,_bottomright)
  {
    creator->rectangles.push_back(this);
  }
}

>>>>>>> 09b7cc8 (reinit commit)
#endif