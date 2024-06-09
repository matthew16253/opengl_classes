#ifndef KEY_CALLBACKS_HPP
#define KEY_CALLBACKS_HPP

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include"../fd_decs.hpp"

namespace myui
{
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
    }
  }

  void keyRepeatInputMainloop()
  {
    globalPerformanceAndState.updateDeltaTime();

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
      if(lastTextItemPressed && globalPerformanceAndState.keyPressed(GLFW_KEY_LEFT))
      {
        lastTextItemPressed->tryMoveBlinker(-1);
      }
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
      if(lastTextItemPressed && globalPerformanceAndState.keyPressed(GLFW_KEY_RIGHT))
      {
        lastTextItemPressed->tryMoveBlinker(1);
      }
    }
    else if(glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
    {
      if(lastTextItemPressed && globalPerformanceAndState.keyPressed(GLFW_KEY_BACKSPACE))
      {
        lastTextItemPressed->tryRemoveText();
      }
    }
    else
    {
      globalPerformanceAndState.keyReleased();
    }
  }

  void mouseCallback(GLFWwindow* window, int button, int action, int mods)
  {
    double xpos,ypos;
    glfwGetCursorPos(window,&xpos,&ypos);
    if(button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS)
    {
      for(auto displayIterator = UIManager.displays.begin(); displayIterator != UIManager.displays.end(); displayIterator++)
      {
        if((*displayIterator)->active)
        {
          (*displayIterator)->checkButtonClicks(xpos,ypos);
        }
      }
    }
  }

  void charCallback(GLFWwindow* window, unsigned int codepoint)
  {
    char keyPressed = static_cast<char>(codepoint);
    if(lastTextItemPressed)
    {
      lastTextItemPressed->tryAddText(keyPressed);
    }
  }
}





#endif