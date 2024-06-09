#ifndef TEXTURE_H
#define TEXTURE_H
#include<glad/glad.h>
//#include<glfw/glfw3.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#endif

#include<string>
#include<iostream>

#define DEFAULT_WRAP_S GL_REPEAT
#define DEFAULT_WRAP_T GL_REPEAT
#define DEFAULT_MIN_FILTER GL_LINEAR_MIPMAP_LINEAR
#define DEFAULT_MAG_FILTER GL_LINEAR

class Texture2D
{
  public:
    unsigned int ID;
    //Texture2D();
    void generate(std::string filePath,unsigned int wrapS,unsigned int wrapT,unsigned int minFilter,unsigned int magFilter,unsigned int internalFormat,unsigned int imageFormat,int imageDimensions[2])
    {
      if(imageDimensions == nullptr)
      {
        int width,height,nrChannel;
        unsigned char* data = stbi_load(filePath.c_str(),&width,&height,&nrChannel,0);
        //glActiveTexture(GL_TEXTURE0+num);
        glGenTextures(1,&ID);
        glBindTexture(GL_TEXTURE_2D,ID);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrapS);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);
        //std::cout<<"\n"<<stbi_failure_reason()<<"\n";
        if(data!=NULL)
        {
          glTexImage2D(GL_TEXTURE_2D,0,internalFormat,width,height,0,imageFormat,GL_UNSIGNED_BYTE,data);
          glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{std::cout<<"Failed to load texture";throw std::runtime_error("faied to load texture");}
        stbi_image_free(data);
      }
      else
      {
        int nrChannel;
        unsigned char* data = stbi_load(filePath.c_str(),imageDimensions,imageDimensions+1,&nrChannel,0);
        //glActiveTexture(GL_TEXTURE0+num);
        glGenTextures(1,&ID);
        glBindTexture(GL_TEXTURE_2D,ID);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrapS);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);
        //std::cout<<"\n"<<stbi_failure_reason()<<"\n";
        if(data!=NULL)
        {
          glTexImage2D(GL_TEXTURE_2D,0,internalFormat,imageDimensions[0],imageDimensions[1],0,imageFormat,GL_UNSIGNED_BYTE,data);
          glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{std::cout<<"Failed to load texture";throw std::runtime_error("faied to load texture");}
        stbi_image_free(data);
      }
    }
    void bind()
    {
      glBindTexture(GL_TEXTURE_2D,ID);
    }
    ~Texture2D()
    {
      glDeleteTextures(1,&ID);
    }
};
#endif