#ifndef GENERAL_HELPERS_HPP
#define GENERAL_HELPERS_HPP

#include"../fd_decs.hpp"
#include<string>

namespace myui
{
  template<typename T>
  void constrainedChange(T& base, T change, T lowerBound, T upperBound)
  {
    base += change;
    if(base > upperBound){base = upperBound;}
    if(base < lowerBound){base = lowerBound;}
  }
}



#endif