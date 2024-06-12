#ifndef RECTANGLE_MANAGER_HPP
#define RECTANGLE_MANAGER_HPP

#include"../fd_decs.hpp"
#include"../GL_class_manager.hpp"


#include<glad/glad.h>
#include<glfw/glfw3.h>



namespace myui
{
  // RectangleManager::RectangleManager(DisplayRenderTools* _renderkit) : renderKit(_renderkit)
  // {
  //   glGenVertexArrays(1,&renderKit->globalRenderTools.VAO);
  //   glGenBuffers(1,&renderKit->globalRenderTools.VBO);

  //   glBindVertexArray(renderKit->globalRenderTools.VAO);
  //   glBindBuffer(GL_ARRAY_BUFFER, renderKit->globalRenderTools.VBO);

  //   glBufferData(GL_ARRAY_BUFFER,6*4*sizeof(float),NULL,GL_DYNAMIC_DRAW);
  //   glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0); // vertex pos
  //   glEnableVertexAttribArray(0);
  //   glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float))); // texture coords
  //   glEnableVertexAttribArray(1);
  // }


  void Display::renderRectangles()
  {
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(globalRenderKit.VAO);
    glBindBuffer(GL_ARRAY_BUFFER,globalRenderKit.VBO);
    
    globalRenderKit.shader.use();
    globalRenderKit.shader.setMat4("UniformProjection", globalRenderKit.projectionMatrix);
    globalRenderKit.shader.setMat4("UniformModel", modelMatrix);
    globalRenderKit.shader.setInt("UniformTexture", 0);
    for(auto rectIterator = rectangles.begin(); rectIterator != rectangles.end(); rectIterator++)
    {
      if((*rectIterator)->shouldRender)
      {
        //std::cout<<(*rectIterator)->topleft.x<<","<<(*rectIterator)->topleft.y<<"   "<<(*rectIterator)->bottomright.x
        //         <<(*rectIterator)->bottomright.y<<"\n";
        globalRenderKit.shader.setVec4("UniformColor", (*rectIterator)->color);
        (*rectIterator)->texture->bind();
        float vertices[6*4] =
        {(*rectIterator)->topleft.x,      (*rectIterator)->topleft.y,  0.0f,0.0f,
          (*rectIterator)->bottomright.x, (*rectIterator)->topleft.y,   1.0f,0.0f,
          (*rectIterator)->topleft.x,      (*rectIterator)->bottomright.y,  0.0f,1.0f,
          
          (*rectIterator)->bottomright.x,  (*rectIterator)->topleft.y,     1.0f,0.0f,
          (*rectIterator)->topleft.x,           (*rectIterator)->bottomright.y,  0.0f,1.0f,
          (*rectIterator)->bottomright.x,    (*rectIterator)->bottomright.y   ,1.0f,1.0f
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
      }
    }
  }
}



#endif