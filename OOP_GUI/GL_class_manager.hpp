#ifndef GL_CLASS_MANAGER_HPP
#define GL_CLASS_MANAGER_HPP

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace ResourceManager
{
    void initGLFW()
    {
      if(!glfwInit()){throw std::runtime_error("failed to init glad");}
    }
    void initGLAD()
    {
      if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){throw std::runtime_error("glad failed to load. try again bozo");}
    }
    GLFWwindow* createWindow(int width,int height,bool resizeable)
    {
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE,resizeable);
      GLFWwindow* newWindow=glfwCreateWindow(width,height,"my learning project",NULL,NULL);
      if(newWindow==NULL){throw std::runtime_error("window failed to generate");}
      glfwMakeContextCurrent(newWindow);
      return newWindow;
    }
    void getShader(Shader* location,std::string vertexShaderPath,std::string fragmentShaderPath)
    {
      location->generate(vertexShaderPath.c_str(),fragmentShaderPath.c_str());
    }
    void getNewTexture(Texture2D* location,std::string imgFileName,bool alpha)
    {
      location->generate(imgFileName,DEFAULT_WRAP_S,DEFAULT_WRAP_T,DEFAULT_MIN_FILTER,DEFAULT_MAG_FILTER,GL_RGB+alpha,GL_RGB+alpha,nullptr);
    }
    void getCustomTexture(Texture2D* location,std::string imgFileName,unsigned int wrapX,unsigned int wrapY,
    unsigned int minimiseFilter,unsigned int magnifyFilter,unsigned int internalFormat,unsigned int imageFormat,int* dimensions)
    {
      location->generate(imgFileName,wrapX,wrapY,minimiseFilter,magnifyFilter,internalFormat,imageFormat,dimensions);
    }
    void getRedTexture(Texture2D* location,std::string imgFileName){
      glPixelStorei(GL_UNPACK_ALIGNMENT,1);
      location->generate(imgFileName,DEFAULT_WRAP_S,DEFAULT_WRAP_T,DEFAULT_MIN_FILTER,DEFAULT_MAG_FILTER,GL_RED,GL_RED,nullptr);
    }
};


void formatRGB(float& red,float& green,float& blue)
{
  red /= 255;
  green /= 255;
  blue /= 255;
}



#endif