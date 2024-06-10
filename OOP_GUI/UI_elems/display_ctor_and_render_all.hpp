<<<<<<< HEAD
#ifndef DISPLAY_CTOR_HPP
#define DISPLAY_CTOR_HPP

#include"../fd_decs.hpp"

namespace myui
{
  Display::Display(bool _active,const glm::mat4& _modelMatrix) : modelMatrix(_modelMatrix), active(_active)
  {
    UIManager.displays.push_back(this);
  }
  void Display::renderAll()
  {
    renderRectangles();
    renderTextItems();
  }
}



=======
#ifndef DISPLAY_CTOR_HPP
#define DISPLAY_CTOR_HPP

#include"../fd_decs.hpp"

namespace myui
{
  Display::Display(bool _active,const glm::mat4& _modelMatrix) : modelMatrix(_modelMatrix), active(_active)
  {
    UIManager.displays.push_back(this);
  }
  void Display::renderAll()
  {
    renderRectangles();
    renderTextItems();
  }
}



>>>>>>> 09b7cc8 (reinit commit)
#endif