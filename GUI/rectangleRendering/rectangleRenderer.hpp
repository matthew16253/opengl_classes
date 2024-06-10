#ifndef RECTANGLE_RENDERER
#define RECTANGLE_RENDERER

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<list>
#include<string>

#include<opengl_classes/resource_manager.hpp>
#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>
#include<opengl_classes/GUI/rendererRescources.hpp>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


namespace myui
{
  TexturedButton::TexturedButton(Texture2D* t_texture,glm::vec2 t_topLeftTranslate,glm::vec2 t_scale,bool t_shouldRender,bool t_enabled,void(*t_command)())
      : texture(t_texture),topLeftTranslate(t_topLeftTranslate),scale(t_scale),shouldRender(t_shouldRender),enabled(t_enabled),command(t_command){}

  ColoredButton::ColoredButton(glm::vec4 t_color,glm::vec2 t_topLeftTranslate,glm::vec2 t_scale,bool t_shouldRender,bool t_enabled,void(*t_command)())
      : color(t_color),topLeftTranslate(t_topLeftTranslate),scale(t_scale),shouldRender(t_shouldRender),enabled(t_enabled),command(t_command)  {}

  CustomButton::CustomButton(Texture2D* t_texture,glm::vec4 t_color,glm::vec2 t_topLeftTranslate,glm::vec2 t_scale,bool t_shouldRender,bool t_enabled,void(*t_command)())
      : texture(t_texture),color(t_color),topLeftTranslate(t_topLeftTranslate),scale(t_scale),shouldRender(t_shouldRender),enabled(t_enabled),command(t_command)  {}

  void initRectangleRenderer()
  {
    customRectangleShader = resourceManager::getNewShader("C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/rectangleRendering/shaders/customRectangle.vert",
                                                          "C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/rectangleRendering/shaders/customRectangle.frag");
    coloredRectangleShader = resourceManager::getNewShader("C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/rectangleRendering/shaders/coloredRectangle.vert",
                                                          "C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/rectangleRendering/shaders/coloredRectangle.frag");
    texturedRectangleShader = resourceManager::getNewShader("C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/rectangleRendering/shaders/texturedRectangle.vert",
                                                          "C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/rectangleRendering/shaders/texturedRectangle.frag");

    unsigned int rectangleVBO;
    float rectangleVertices[12] = {0.0f,0.0f,  1.0f,0.0f,   0.0f,1.0f,
                                  0.0f,1.0f,  1.0f,0.0f,   1.0f,1.0f};
    glGenVertexArrays(1,&rectangleVAO);
    glGenBuffers(1,&rectangleVBO);

    glBindVertexArray(rectangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER,rectangleVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(rectangleVertices),rectangleVertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }

  //           TEXTURED BUTTON FACTORY
  TexturedButton* Display::getNewTexturedButton(Texture2D* texture,rectanglePoint point,glm::vec2 pos,glm::vec2 size,void(*command)())
  {
    glm::vec2 newBottomLeftTranslate;
    if(point==TOPLEFT){newBottomLeftTranslate.x=pos.x;newBottomLeftTranslate.y=pos.y;}
    else if(point==TOPRIGHT){newBottomLeftTranslate.x=pos.x-size.x;newBottomLeftTranslate.y=pos.y;}
    else if(point==BOTTOMLEFT){newBottomLeftTranslate.x=pos.x;newBottomLeftTranslate.y=pos.y-size.y;}
    else if(point==BOTTOMRIGHT){newBottomLeftTranslate.x=pos.x-size.x;newBottomLeftTranslate.y=pos.y-size.y;}
    else if(point==CENTER){newBottomLeftTranslate.x=pos.x-(0.5f*size.x);newBottomLeftTranslate.y=pos.y-(0.5f*size.y);}
    TexturedButton* newButton = new TexturedButton(texture,newBottomLeftTranslate,size,true,true,command);
    texturedButtonList.push_back(newButton);
    return newButton;
  }
  TexturedButton* Display::getNewTexturedButton(Texture2D* texture,rectanglePoint point1,glm::vec2 pos1,rectanglePoint point2,glm::vec2 pos2,void(*command)())
  {
    glm::vec2 newBottomLeftTranslate,size;
    if(point1==TOPLEFT&&point2==BOTTOMRIGHT){newBottomLeftTranslate.x=pos1.x;newBottomLeftTranslate.y=pos1.y;}
    else if(point1==BOTTOMRIGHT&&point2==TOPLEFT){newBottomLeftTranslate.x=pos2.x;newBottomLeftTranslate.y=pos2.y;}
    else if(point1==TOPRIGHT&&point2==BOTTOMLEFT){newBottomLeftTranslate.x=pos2.x;newBottomLeftTranslate.y=pos1.y;}
    else if(point1==BOTTOMLEFT&&point2==TOPRIGHT){newBottomLeftTranslate.x=pos1.x;newBottomLeftTranslate.y=pos2.y;}
    TexturedButton* newButton = new TexturedButton(texture,newBottomLeftTranslate,size,true,true,command);
    texturedButtonList.push_back(newButton);
    return newButton;
  }

  //     COLORED BUTTON FACTORY

  ColoredButton* Display::getNewColoredButton(glm::vec4 color,rectanglePoint point,glm::vec2 pos,glm::vec2 size,void(*command)())
  {
    glm::vec2 newBottomLeftTranslate;
    if(point==TOPLEFT){newBottomLeftTranslate.x=pos.x;newBottomLeftTranslate.y=pos.y;}
    else if(point==TOPRIGHT){newBottomLeftTranslate.x=pos.x-size.x;newBottomLeftTranslate.y=pos.y;}
    else if(point==BOTTOMLEFT){newBottomLeftTranslate.x=pos.x;newBottomLeftTranslate.y=pos.y-size.y;}
    else if(point==BOTTOMRIGHT){newBottomLeftTranslate.x=pos.x-size.x;newBottomLeftTranslate.y=pos.y-size.y;}
    else if(point==CENTER){newBottomLeftTranslate.x=pos.x-(0.5f*size.x);newBottomLeftTranslate.y=pos.y-(0.5f*size.y);}
    ColoredButton* newButton = new ColoredButton(color,newBottomLeftTranslate,size,true,true,command);
    coloredButtonList.push_back(newButton);
    return newButton;
  }
  ColoredButton* Display::getNewColoredButton(glm::vec4 color,rectanglePoint point1,glm::vec2 pos1,rectanglePoint point2,glm::vec2 pos2,void(*command)())
  {
    glm::vec2 newBottomLeftTranslate,size;
    if(point1==TOPLEFT&&point2==BOTTOMRIGHT){newBottomLeftTranslate.x=pos1.x;newBottomLeftTranslate.y=pos1.y;}
    else if(point1==BOTTOMRIGHT&&point2==TOPLEFT){newBottomLeftTranslate.x=pos2.x;newBottomLeftTranslate.y=pos2.y;}
    else if(point1==TOPRIGHT&&point2==BOTTOMLEFT){newBottomLeftTranslate.x=pos2.x;newBottomLeftTranslate.y=pos1.y;}
    else if(point1==BOTTOMLEFT&&point2==TOPRIGHT){newBottomLeftTranslate.x=pos1.x;newBottomLeftTranslate.y=pos2.y;}
    ColoredButton* newButton = new ColoredButton(color,newBottomLeftTranslate,size,true,true,command);
    coloredButtonList.push_back(newButton);
    return newButton;
  }

  //     CUSTOM BUTTON FACTORY

  CustomButton* Display::getNewCustomButton(Texture2D* texture,glm::vec4 color,rectanglePoint point,glm::vec2 pos,glm::vec2 size,void(*command)())
  {
    glm::vec2 newBottomLeftTranslate;
    if(point==TOPLEFT){newBottomLeftTranslate.x=pos.x;newBottomLeftTranslate.y=pos.y;}
    else if(point==TOPRIGHT){newBottomLeftTranslate.x=pos.x-size.x;newBottomLeftTranslate.y=pos.y;}
    else if(point==BOTTOMLEFT){newBottomLeftTranslate.x=pos.x;newBottomLeftTranslate.y=pos.y-size.y;}
    else if(point==BOTTOMRIGHT){newBottomLeftTranslate.x=pos.x-size.x;newBottomLeftTranslate.y=pos.y-size.y;}
    else if(point==CENTER){newBottomLeftTranslate.x=pos.x-(0.5f*size.x);newBottomLeftTranslate.y=pos.y-(0.5f*size.y);}
    CustomButton* newButton = new CustomButton(texture,color,newBottomLeftTranslate,size,true,true,command);
    customButtonList.push_back(newButton);
    return newButton;
  }
  CustomButton* Display::getNewCustomButton(Texture2D* texture,glm::vec4 color,rectanglePoint point1,glm::vec2 pos1,rectanglePoint point2,glm::vec2 pos2,void(*command)())
  {
    glm::vec2 newBottomLeftTranslate,size;
    if(point1==TOPLEFT&&point2==BOTTOMRIGHT){newBottomLeftTranslate.x=pos1.x;newBottomLeftTranslate.y=pos1.y;}
    else if(point1==BOTTOMRIGHT&&point2==TOPLEFT){newBottomLeftTranslate.x=pos2.x;newBottomLeftTranslate.y=pos2.y;}
    else if(point1==TOPRIGHT&&point2==BOTTOMLEFT){newBottomLeftTranslate.x=pos2.x;newBottomLeftTranslate.y=pos1.y;}
    else if(point1==BOTTOMLEFT&&point2==TOPRIGHT){newBottomLeftTranslate.x=pos1.x;newBottomLeftTranslate.y=pos2.y;}
    CustomButton* newButton = new CustomButton(texture,color,newBottomLeftTranslate,size,true,true,command);
    customButtonList.push_back(newButton);
    return newButton;
  }

  //     BUTTON RENDERING
  void Display::renderAllButtons(bool renderTextured,bool renderColored,bool renderCustom)
  {
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(rectangleVAO);
    if(renderTextured)
    {
      texturedRectangleShader->use();
      texturedRectangleShader->setMat4("projection",projection);
      for(auto it = texturedButtonList.begin();it!=texturedButtonList.end();it++)
      {
        if((*it)->shouldRender)
        {
          glm::mat4 rectModel = glm::mat4(1.0f);
          rectModel = glm::translate(rectModel,glm::vec3((*it)->topLeftTranslate,0.0f));
          rectModel = model * glm::scale(rectModel,glm::vec3((*it)->scale,0.0f));
          texturedRectangleShader->setMat4("model",rectModel);
          (*it)->texture->bind();
          texturedRectangleShader->setInt("ourTexture",0);
          glDrawArrays(GL_TRIANGLES,0,6);
        }
      }
    }
    if(renderColored)
    {
      coloredRectangleShader->use();
      coloredRectangleShader->setMat4("projection",projection);
      for(auto it = coloredButtonList.begin();it!=coloredButtonList.end();it++)
      {
        if((*it)->shouldRender)
        {
          glm::mat4 rectModel = glm::mat4(1.0f);
          rectModel = glm::translate(rectModel,glm::vec3((*it)->topLeftTranslate,0.0f));
          rectModel = model * glm::scale(rectModel,glm::vec3((*it)->scale,0.0f));
          coloredRectangleShader->setMat4("model",model);
          coloredRectangleShader->setVec4("ourColor",(*it)->color);
          glDrawArrays(GL_TRIANGLES,0,6);
        }
      }
    }
    if(renderCustom)
    {
      customRectangleShader->use();
      customRectangleShader->setMat4("projection",projection);
      for(auto it = customButtonList.begin();it!=customButtonList.end();it++)
      {
        std::cout<<"rendering first sutoms";
        if((*it)->shouldRender)
        {
          glm::mat4 model = glm::mat4(1.0f);
          model = glm::translate(model,glm::vec3((*it)->topLeftTranslate,0.0f));
          model = glm::scale(model,glm::vec3((*it)->scale,0.0f));
          customRectangleShader->setMat4("model",model);
          (*it)->texture->bind();
          customRectangleShader->setInt("ourTexture",0);
          customRectangleShader->setVec4("ourColor",(*it)->color);
          glDrawArrays(GL_TRIANGLES,0,6);
        }
      }
    }
    glBindVertexArray(0);
  }

  //     BUTTON DELETER
  void Display::deleteButton(ColoredButton* button)
  {
    coloredButtonList.remove(button);
    delete button;
  }
  void Display::deleteButton(TexturedButton* button)
  {
    texturedButtonList.remove(button);
    delete button;
  }
  void Display::deleteButton(CustomButton* button)
  {
    customButtonList.remove(button);
    delete button;
  }

  //       BUTTON DELETER FOR ALL BUTTONS
  void Display::deleteAllButtons(bool deleteTextured,bool deleteColored,bool deleteCustom)
  {
    if(deleteColored)
    {
      for(auto it = coloredButtonList.begin();it!=coloredButtonList.end();it++)
      {
        coloredButtonList.erase(it);
        delete *it;
      }
    }
    if(deleteTextured)
    {
      for(auto it = texturedButtonList.begin();it!=texturedButtonList.end();it++)
      {
        texturedButtonList.erase(it);
        delete *it;
      }
    }
    if(deleteCustom)
    {
      for(auto it = customButtonList.begin();it!=customButtonList.end();it++)
      {
        customButtonList.erase(it);
        delete *it;
      }
    }
  }

  //      CHECK FOR BUTTON CLICKS
  void Display::checkButtonClicksCallback(bool checkTextured,bool checkColored,bool checkCustom,double xpos,double ypos)
  {
    if(checkTextured)
    {
      for(auto it = texturedButtonList.begin();it!=texturedButtonList.end();it++)
      {
        if((*it)->enabled)
        {
          if((((*it)->topLeftTranslate.x)<xpos && xpos<((*it)->topLeftTranslate.x+(*it)->scale.x))  &&
             (((*it)->topLeftTranslate.y)<ypos && ypos<((*it)->topLeftTranslate.y+(*it)->scale.y)))
             {
              (*it)->command();
              break;
             }
        }
      }
    }
    if(checkColored)
    {
      for(auto it = coloredButtonList.begin();it!=coloredButtonList.end();it++)
      {
        if((*it)->enabled)
        {
          if((((*it)->topLeftTranslate.x)<xpos && xpos<((*it)->topLeftTranslate.x+(*it)->scale.x))  &&
             (((*it)->topLeftTranslate.y)<ypos && ypos<((*it)->topLeftTranslate.y+(*it)->scale.y)))
             {
              (*it)->command();
              break;
             }
        }
      }
    }
    if(checkCustom)
    {
      for(auto it = customButtonList.begin();it!=customButtonList.end();it++)
      {
        if((*it)->enabled)
        {
          if((((*it)->topLeftTranslate.x)<xpos && xpos<((*it)->topLeftTranslate.x+(*it)->scale.x))  &&
             (((*it)->topLeftTranslate.y)<ypos && ypos<((*it)->topLeftTranslate.y+(*it)->scale.y)))
             {
              (*it)->command();
              break;
             }
        }
      }
    }
  }
}

#endif