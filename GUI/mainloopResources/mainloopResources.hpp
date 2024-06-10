#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/GUI/rendererRescources.hpp>


namespace myui
{
  void updateDeltaTime()
  {
    deltaTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();
  }
  void tryEditTextboxes(int codepoint)
  {
    char c = static_cast<char>(codepoint);
    currentDisplay->tryAddTextCallback(c);
  }
  void checkTextboxClicks(int mouseX,int mouseY)
  {
    currentDisplay->checkTextboxClicksCallback(mouseX,mouseY);
  }
  void checkButtonClicks(int mouseX,int mouseY)
  {
    currentDisplay->checkButtonClicksCallback(true,true,true,mouseX,mouseY);
  }
  void checkClicks(int mouseX,int mouseY)
  {
    checkButtonClicks(mouseX,mouseY);
    checkTextboxClicks(mouseX,mouseY);
  }
  void tryScrollTextboxes(GLFWwindow* window)
  {
    if(textboxScrollCountdown != 0){textboxScrollCountdown--;}
    if(glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)
    {
      if(textboxScrollCountdown==0){currentDisplay->tryMoveTextboxCallback(-1);textboxScrollCountdown=textboxScrollSpeed;}
    }
    else if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)
    {
      if(textboxScrollCountdown==0){currentDisplay->tryMoveTextboxCallback(1);textboxScrollCountdown=textboxScrollSpeed;}
    }
    else if(glfwGetKey(window,GLFW_KEY_BACKSPACE)==GLFW_PRESS)
    {
      if(textboxScrollCountdown==0){currentDisplay->removeTextCallback();textboxScrollCountdown=textboxScrollSpeed;}
    }
  }
}