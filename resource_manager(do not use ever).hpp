#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/FPcamera.hpp>
#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include<string>

class resourceManager
{
  private:
  public:
    static void initGLFW()
    {
      if(!glfwInit()){throw std::runtime_error("failed to init glad");}
    }
    static void initGLAD()
    {
      if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){throw std::runtime_error("glad failed to load. try again bozo");}
    }
    static GLFWwindow* createWindow(int width,int height,bool resizeable)
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
    static Shader* getNewShader(std::string vertexShaderPath,std::string fragmentShaderPath){return new Shader(vertexShaderPath.c_str(),fragmentShaderPath.c_str());}
    static Texture2D* getNewTexture(std::string imgFileName,bool alpha)
    {
      Texture2D* new_texture = new Texture2D();
      new_texture->generate(imgFileName,DEFAULT_WRAP_S,DEFAULT_WRAP_T,DEFAULT_MIN_FILTER,DEFAULT_MAG_FILTER,GL_RGB+alpha,GL_RGB+alpha,nullptr);
      return new_texture;
    }
    static Texture2D* getCustomTexture(std::string imgFileName,unsigned int wrapX,unsigned int wrapY,unsigned int minimiseFilter,unsigned int magnifyFilter,unsigned int internalFormat,unsigned int imageFormat,int* dimensions)
    {
      Texture2D* new_texture = new Texture2D();
      new_texture->generate(imgFileName,wrapX,wrapY,minimiseFilter,magnifyFilter,internalFormat,imageFormat,dimensions);
      return new_texture;
    }
    static Texture2D* getRedTexture(std::string imgFileName){
      Texture2D* new_texture = new Texture2D();
      glPixelStorei(GL_UNPACK_ALIGNMENT,1);
      new_texture->generate(imgFileName,DEFAULT_WRAP_S,DEFAULT_WRAP_T,DEFAULT_MIN_FILTER,DEFAULT_MAG_FILTER,GL_RED,GL_RED,nullptr);
      return new_texture;
    }
    static void formatRGB(float& red,float& green,float& blue)
    {
      red /= 255;
      green /= 255;
      blue /= 255;
    }
};

#endif