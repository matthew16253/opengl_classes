#ifndef BUTTON_AREA_HPP
#define BUTTON_AREA_HPP

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include"../fd_decs.hpp"



namespace myui
{
      Button::Button(Display* creator, const glm::vec2 _topleft, const glm::vec2 _bottomright, Texture2D* _texture,
	     glm::vec4 _color, bool _shouldRender, void(*_command)(double,double), bool _buttonEnabled)
       : command(_command), buttonEnabled(_buttonEnabled),
         Rectangle(creator,_topleft,_bottomright,_texture,_color,_shouldRender)
      {
        creator->buttonAreas.push_back(this);
      }
}

#endif