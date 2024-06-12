#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"../fd_decs.hpp"

namespace myui
{
  void Display::checkButtonClicks(double xpos, double ypos)
  {
    for(auto buttonIterator = buttonAreas.begin(); buttonIterator != buttonAreas.end(); buttonIterator++)
    {
      if((*buttonIterator)->buttonEnabled)
      {
      // PLEASE CHECK IF THIS IS VALID, IM NOT SURE ABOUT THE DIRECTION OF Y AXIS
        float z;
        glReadPixels(xpos,ypos,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);
        glm::vec3 coord = glm::unProject(glm::vec3(xpos,DEFAULT_HEIGHT-ypos,z),modelMatrix,globalRenderKit.projectionMatrix,glm::vec4(0,0,DEFAULT_WIDTH,DEFAULT_HEIGHT));
        if((*buttonIterator)->topleft.x < coord.x && coord.x < (*buttonIterator)->bottomright.x && 
        (*buttonIterator)->topleft.y < coord.y && coord.y < (*buttonIterator)->bottomright.y)
        {
          if(dynamic_cast<TextItem*>(*buttonIterator))
          {
            lastTextItemPressed = static_cast<TextItem*>(*buttonIterator);
            lastButtonPressed = nullptr;
          }
          else if(dynamic_cast<Button*>(*buttonIterator))
          {
            lastButtonPressed = *buttonIterator;
            lastTextItemPressed = nullptr;
          }
          (*buttonIterator)->command(xpos,ypos);
                    //     MAKE command AN ENUMERATION FUNCTION OF ENUM enum UIElemType{RECTANGLE,TEXT_ITEM, etc}, and
          // depending on the return value, set the current textbox to the  (upcasted) button pointer whenever clicked
        }
      }
    }
  }
}



#endif