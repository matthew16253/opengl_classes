#ifndef AREA_HPP
#define AREA_HPP

#include"../fd_decs.hpp"

namespace myui
{
  Area::Area(Display* creator, const glm::vec2 _topleft, const glm::vec2 _bottomright)
   : topleft(glm::vec2(std::min(_topleft.x,_bottomright.x),std::min(_topleft.y,_bottomright.y))),
    bottomright(glm::vec2(std::max(_topleft.x,_bottomright.x),std::max(_topleft.y,_bottomright.y)))
  {
    creator->areas.push_back(this);
  }
}


#endif