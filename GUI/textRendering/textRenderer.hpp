#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<list>
#include<string>
#include<map>

#include<opengl_classes/resource_manager.hpp>
#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>
#include<opengl_classes/GUI/rendererRescources.hpp>
#include<opengl_classes/charTextureGenerator/charTextureGenerator.hpp>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace myui
{

  FixedTextbox::FixedTextbox(std::string t_text,glm::vec4 t_color,glm::vec4 t_bgcolor,float t_scaleX,float t_scaleY,int t_topLeftX,int t_topLeftY,int t_widthLimit,bool t_shouldRender,int t_startChar,bool t_canWriteTo,int t_blinkerStart)
      : text(t_text),color(t_color),bgcolor(t_bgcolor),scaleX(t_scaleX),scaleY(t_scaleY),topLeftX(t_topLeftX),topLeftY(t_topLeftY),widthLimit(t_widthLimit),shouldRender(t_shouldRender),startChar(t_startChar),canWriteTo(t_canWriteTo),blinkerStart(t_blinkerStart)  {}

  DynamicTextbox::DynamicTextbox(std::string t_text,glm::vec4 t_color,glm::vec4 t_bgcolor,float t_scaleX,float t_scaleY,int t_topLeftX,int t_topLeftY,int t_width,bool t_shouldRender,bool t_canWriteTo,int t_blinkerStart)
      : text(t_text),color(t_color),bgcolor(t_bgcolor),scaleX(t_scaleX),scaleY(t_scaleY),topLeftX(t_topLeftX),topLeftY(t_topLeftY),width(t_width),shouldRender(t_shouldRender),canWriteTo(t_canWriteTo),blinkerStart(t_blinkerStart)  {}
  
  //      INITIALIZE THE TEXT RENDERER
  void initTextRenderer()
  {
    textShader = resourceManager::getNewShader("C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/textRendering/shaders/character.vert",
                                               "C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/textRendering/shaders/character.frag");
    textbgShader = resourceManager::getNewShader("C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/textRendering/shaders/textbg.vert",
                                               "C:/Users/matth/Documents/coding/OpenGL_resources/opengl_include/opengl_classes/GUI/textRendering/shaders/textbg.frag");
    for(char currentChar = 32;currentChar<127;currentChar++)
    {
      int dimensions[2];
      Texture2D* texture = CharTexturizer::toNewTexture(currentChar,dimensions); // this is on the heap REMEMBER
      characterMap[currentChar] = characterData{texture,dimensions[0],dimensions[1]};
      std::cout<<"height: "<<characterMap[currentChar].height<<"     width:  "<<characterMap[currentChar].width<<std::endl;
      std::cout<<currentChar;
    }
    glGenVertexArrays(1,&textVAO);
    glGenBuffers(1,&textVBO);

    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER,textVBO);

    glBufferData(GL_ARRAY_BUFFER,6*4*sizeof(float),NULL,GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

//textbg
    glGenVertexArrays(1,&textbgVAO);
    glGenBuffers(1,&textbgVBO);

    glBindVertexArray(textbgVAO);
    glBindBuffer(GL_ARRAY_BUFFER,textbgVBO);

    glBufferData(GL_ARRAY_BUFFER,6*2*sizeof(float),NULL,GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }

  //      TEXTBOX FACTORIES
  FixedTextbox* Display::getNewFixedTextbox(const std::string& text,glm::vec4 textColor,glm::vec4 bgcolor,glm::vec2 textScale,glm::ivec2 topLeft,int widthLimit,bool canWriteTo)
  {
    FixedTextbox* textbox = new FixedTextbox{text,textColor,bgcolor,textScale.x,textScale.y,topLeft.x,topLeft.y,widthLimit,true,0,canWriteTo,0};
    fixedTextBoxList.push_back(textbox);
    return textbox;
  }
  DynamicTextbox* Display::getNewDynamicTextbox(const std::string& text,glm::vec4 textColor,glm::vec4 bgcolor,glm::vec2 textScale,glm::ivec2 topLeft,bool canWriteTo)
  {
    DynamicTextbox* textbox = new DynamicTextbox{text,textColor,bgcolor,textScale.x,textScale.y,topLeft.x,topLeft.y,true,getPixelWidth(text,textScale.x),0,canWriteTo};
    dynamicTextBoxList.push_back(textbox);
    return textbox;
  }
  void Display::changeText(FixedTextbox* textbox,const std::string& newText)
  {
    textbox->text = newText;
  }
  void Display::changeText(DynamicTextbox* textbox,const std::string& newText)
  {
    textbox->text = newText;
    textbox->width = getPixelWidth(newText,textbox->scaleX);
  }
  void Display::addText(FixedTextbox* textbox,const std::string& newText)
  {
    textbox->text += newText;
  }
  void Display::addText(DynamicTextbox* textbox,const std::string& newText)
  {
    textbox->text += newText;
    textbox->width += getPixelWidth(newText,textbox->scaleX);
  }
  void Display::addText(FixedTextbox* textbox,char newText,int index)
  {
    textbox->text.insert(textbox->text.begin()+index,newText);
  }
  void Display::addText(DynamicTextbox* textbox,char newText,int index)
  {
    if(textbox == nullptr){std::cout<<"rizz";}
    textbox->text.insert(textbox->text.begin()+index,newText);
    textbox->width += getPixelWidth(std::string(1,newText),textbox->scaleX);
  }
  void Display::removeText(FixedTextbox* textbox,int index)
  {
    textbox->text.erase(textbox->text.begin()+index);
  }
  void Display::removeText(DynamicTextbox* textbox,int index)
  {
    textbox->width -= getPixelWidth(std::string(1,textbox->text.at(index)),textbox->scaleX);
    textbox->text.erase(textbox->text.begin()+index);
  }
  void Display::prepareTextboxRender()
  {
    textShader->use();
    textShader->setInt("ourTexture",0);
    textShader->setMat4("projection",projection);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER,textVBO);
  }
  //void Display::renderFixedTextbox(FixedTextbox* textbox);
  //void Display::renderDynamicTextbox(DynamicTextbox* textbox);
  void Display::renderAllTextboxes(bool renderFixed,bool renderDynamic)
  {
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textbgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textbgVBO);

    textbgShader->use();
    textbgShader->setMat4("projection",projection);
    textbgShader->setMat4("model",model);
    if(renderDynamic)
    {
      for(auto itTextbox = dynamicTextBoxList.begin();itTextbox!=dynamicTextBoxList.end();itTextbox++)
      {
        if((*itTextbox)->shouldRender && true)
        {
          DynamicTextbox* textbox = *itTextbox;
          textbgShader->setVec4("ourColor",textbox->bgcolor);
          float vertices[] = {textbox->topLeftX               ,   textbox->topLeftY,
                              textbox->topLeftX+textbox->width,   textbox->topLeftY,
                              textbox->topLeftX               ,   textbox->topLeftY+textbox->scaleY*700,
                              
                              textbox->topLeftX+textbox->width,   textbox->topLeftY,
                              textbox->topLeftX               ,   textbox->topLeftY+textbox->scaleY*700,
                              textbox->topLeftX+textbox->width,   textbox->topLeftY+textbox->scaleY*700};
          glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
          glDrawArrays(GL_TRIANGLES,0,6);
        }
      }
    }
    if(renderFixed && true)
    {
      for(auto itTextbox = fixedTextBoxList.begin();itTextbox!=fixedTextBoxList.end();itTextbox++)
      {
        if((*itTextbox)->shouldRender)
        {
          FixedTextbox* textbox = *itTextbox;
          textbgShader->setVec4("ourColor",textbox->bgcolor);
          float vertices[] = {textbox->topLeftX               ,   textbox->topLeftY,
                              textbox->topLeftX+textbox->widthLimit,   textbox->topLeftY,
                              textbox->topLeftX               ,   textbox->topLeftY+textbox->scaleY*700,
                              
                              textbox->topLeftX+textbox->widthLimit,   textbox->topLeftY,
                              textbox->topLeftX               ,   textbox->topLeftY+textbox->scaleY*700,
                              textbox->topLeftX+textbox->widthLimit,   textbox->topLeftY+textbox->scaleY*700};
          glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
          glDrawArrays(GL_TRIANGLES,0,6);
        }
      }
    }
//draw actual text
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);

    textShader->use();
    textShader->setInt("ourTexture",0);
    textShader->setMat4("projection",projection);
    textShader->setMat4("model",model);
    if(renderDynamic)
    {
      for(auto itTextbox = dynamicTextBoxList.begin();itTextbox!=dynamicTextBoxList.end();itTextbox++)
      {
        if((*itTextbox)->shouldRender)
        {
          DynamicTextbox* textbox = *itTextbox;
          textShader->setVec4("ourColor",textbox->color);
          float currentX = textbox->topLeftX;
          const float currentY = textbox->topLeftY;
          float pixelHeight = 700 * textbox->scaleY;
          for(int itCharacter = 0;itCharacter!=textbox->text.length();itCharacter++)
          {
            characterData currentCharRenderInfo = characterMap[textbox->text.at(itCharacter)];
            float pixelWidth = currentCharRenderInfo.width * textbox->scaleX;
            if(selectedDynamicTextbox==textbox && itCharacter==textbox->blinkerStart){renderCharacter('|',glm::vec2(0.1f,1.0f),glm::ivec2(currentX,currentY));}
            float vertices[] = {currentX           , currentY                ,0.0f,0.0f,
                                currentX+pixelWidth, currentY                ,1.0f,0.0f,
                                currentX           , currentY+pixelHeight    ,0.0f,1.0f,
                                
                                currentX+pixelWidth, currentY                ,1.0f,0.0f,
                                currentX           , currentY+pixelHeight    ,0.0f,1.0f,
                                currentX+pixelWidth, currentY+pixelHeight    ,1.0f,1.0f};
            currentCharRenderInfo.texture->bind();

            //glBindBuffer(GL_ARRAY_BUFFER,textVBO);
            glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
            //glBindBuffer(GL_ARRAY_BUFFER,0);

            //std::cout<<"\nhere1";
            //std::cout<<currentX<<" "<<currentY<<std::endl;
            glDrawArrays(GL_TRIANGLES,0,6);
            //std::cout<<"\nhere2";

            currentX += pixelWidth;
          }
        }
      }
    }
    if(renderFixed)
    {
      for(auto itTextbox = fixedTextBoxList.begin();itTextbox!=fixedTextBoxList.end();itTextbox++)
      {
        if((*itTextbox)->shouldRender)
        {
          FixedTextbox* textbox = *itTextbox;
          textShader->setVec4("ourColor",textbox->color);
          float currentX = textbox->topLeftX;
          const float currentY = textbox->topLeftY;
          float pixelHeight = 700 * textbox->scaleY;
          if(textbox->blinkerStart < textbox->startChar){tryIncrement<int>(textbox->startChar,-1,0,textbox->text.length()-1);}
          int finalPos = textbox->text.length();
          for(int itCharacter = 0 + textbox->startChar;itCharacter!=textbox->text.length();itCharacter++)
          {
            characterData currentCharRenderInfo = characterMap[textbox->text.at(itCharacter)];
            float pixelWidth = currentCharRenderInfo.width * textbox->scaleX;
            if(selectedFixedTextbox==textbox && itCharacter==textbox->blinkerStart){renderCharacter('|',glm::vec2(0.05f,textbox->scaleY),glm::ivec2(currentX,currentY));}
            if(currentX+pixelWidth > textbox->topLeftX+textbox->widthLimit){finalPos = itCharacter;break;}
            float vertices[] = {currentX           , currentY                ,0.0f,0.0f,
                                  currentX+pixelWidth, currentY                ,1.0f,0.0f,
                                  currentX           , currentY+pixelHeight    ,0.0f,1.0f,
                                  
                                  currentX+pixelWidth, currentY                ,1.0f,0.0f,
                                  currentX           , currentY+pixelHeight    ,0.0f,1.0f,
                                  currentX+pixelWidth, currentY+pixelHeight    ,1.0f,1.0f};
            currentCharRenderInfo.texture->bind();

            glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);

            glDrawArrays(GL_TRIANGLES,0,6);

            currentX += pixelWidth;
          }
          if(selectedFixedTextbox==textbox && textbox->blinkerStart > finalPos){tryIncrement<int>(textbox->startChar,1,0,textbox->text.length()-1);}
          //std::cout<<" startchar = "<<textbox->startChar<<"  blinkerstrat: "<<textbox->blinkerStart<<"  final pos:"<<finalPos<<std::endl;
        }
      }
    }
  }

  //     MAKE THE PROCESS TO MOVE THE POSITION OF FIXEDTEXTBOX
  void Display::checkTextboxClicksCallback(double xpos,double ypos)
  {
    selectedFixedTextbox = nullptr;
    selectedDynamicTextbox = nullptr;
    for(auto itTextbox = fixedTextBoxList.begin();itTextbox!=fixedTextBoxList.end();itTextbox++)
    {
      FixedTextbox* textbox = (*itTextbox);
      int textboxHeight = textbox->scaleY*700;
      if(textbox->topLeftX<xpos && xpos<textbox->topLeftX+textbox->widthLimit &&
         textbox->topLeftY<ypos && ypos<textbox->topLeftY+textboxHeight)
      {
        selectedFixedTextbox = textbox;
        textbox->blinkerStart = getBlinkerStart(textbox,xpos);
        std::cout<<"selected a textbox!!\n";
        break;
      }
    }
    for(auto itTextbox = dynamicTextBoxList.begin();itTextbox!=dynamicTextBoxList.end();itTextbox++)
    {
      DynamicTextbox* textbox = (*itTextbox);
      int textboxHeight = textbox->scaleY*700;
      std::cout<<"wdith: "<<textbox->width<<std::endl;
      if(textbox->topLeftX<xpos && xpos<textbox->topLeftX+textbox->width &&
         textbox->topLeftY<ypos && ypos<textbox->topLeftY+textboxHeight)
      {
        selectedDynamicTextbox = textbox;
        textbox->blinkerStart = getBlinkerStart(textbox,xpos);
        std::cout<<"selected a textbox!!\n";
        break;
      }
    }
  }
  void Display::tryMoveTextboxCallback(int change)
  {
    if(selectedFixedTextbox != nullptr)
    {
      tryIncrement<int>(selectedFixedTextbox->blinkerStart,change,0,selectedFixedTextbox->text.length());
    }
    if(selectedDynamicTextbox != nullptr)
    {
      tryIncrement<int>(selectedDynamicTextbox->blinkerStart,change,0,selectedDynamicTextbox->text.length());
    }
  }
  void Display::removeTextCallback()
  {
    if(selectedDynamicTextbox != nullptr && selectedDynamicTextbox->blinkerStart != 0)
    {
      if(selectedDynamicTextbox->canWriteTo)
      {
        removeText(selectedDynamicTextbox,--selectedDynamicTextbox->blinkerStart);
      }
    }
    else if(selectedFixedTextbox != nullptr && selectedFixedTextbox->blinkerStart != 0)
    {
      if(selectedFixedTextbox->canWriteTo)
      {
        removeText(selectedFixedTextbox,--selectedFixedTextbox->blinkerStart);
        tryLowerBoundedIncrement(selectedFixedTextbox->startChar,-1,0);
      }
    }
  }
  void Display::tryAddTextCallback(char newText)
  {
    bool inMap = false;
    for(auto it = characterMap.begin();it != characterMap.end();it++)
    {
      if((*it).first == newText)
      {
        if(selectedDynamicTextbox != nullptr)
        {
          if(selectedDynamicTextbox->canWriteTo)
          {
            addText(selectedDynamicTextbox,newText,selectedDynamicTextbox->blinkerStart);
            selectedDynamicTextbox->blinkerStart++;
          }
        }
        else if(selectedFixedTextbox != nullptr)
        {
          if(selectedFixedTextbox->canWriteTo)
          {
            addText(selectedFixedTextbox,newText,selectedFixedTextbox->blinkerStart);
            selectedFixedTextbox->blinkerStart++;
          }
        }
        break;
      }
    }
  }
  void Display::prepareCharacterRender()
  {
    //pls complete this
  }
  void Display::renderCharacter(char text,const glm::vec2& scale,const glm::ivec2& topleft)
  {
      characterData currentCharRenderInfo = characterMap[text];
      float pixelWidth = currentCharRenderInfo.width * scale.x;
      const float pixelHeight = currentCharRenderInfo.height * scale.y;
      float vertices[] = {topleft.x           , topleft.y                ,0.0f,0.0f,
                          topleft.x+pixelWidth, topleft.y                ,1.0f,0.0f,
                          topleft.x           , topleft.y+pixelHeight    ,0.0f,1.0f,
                            
                          topleft.x+pixelWidth, topleft.y                ,1.0f,0.0f,
                          topleft.x           , topleft.y+pixelHeight    ,0.0f,1.0f,
                          topleft.x+pixelWidth, topleft.y+pixelHeight    ,1.0f,1.0f};
      currentCharRenderInfo.texture->bind();

      glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);

      glDrawArrays(GL_TRIANGLES,0,6);
  }

  //     DELETE ALL TEXTBOXES
  void Display::deleteAllTextboxes(bool deleteDynamic,bool deleteFixed)
  {
    if(deleteDynamic)
    {
      for(auto itTextbox = dynamicTextBoxList.begin();itTextbox!=dynamicTextBoxList.end();itTextbox++)
      {
        dynamicTextBoxList.erase(itTextbox);
        delete *itTextbox;
      }
    }
    if(deleteFixed)
    {
      for(auto itTextbox = fixedTextBoxList.begin();itTextbox!=fixedTextBoxList.end();itTextbox++)
      {
        fixedTextBoxList.erase(itTextbox);
        delete *itTextbox;
      }
    }
  }

  void Display::deleteTextbox(DynamicTextbox* textbox)
  {
    dynamicTextBoxList.remove(textbox);
    delete textbox;
  }
  void Display::deleteTextbox(FixedTextbox* textbox)
  {
    fixedTextBoxList.remove(textbox);
    delete textbox;
  }
  int getBlinkerStart(const FixedTextbox* textbox,int mouseX)
  {
    int mouseXOffset = mouseX - textbox->topLeftX;
    int currentX = 0;
    if(textbox->text.size() == 0){return 0;}
    for(int currentIndex = textbox->startChar;currentIndex < textbox->text.size();currentIndex++)
    {
      int lastX = currentX;
      currentX += characterMap[textbox->text.at(currentIndex)].width * textbox->scaleX;
      if(currentX > mouseXOffset)
      {
        if(currentX - mouseXOffset > mouseXOffset - lastX)
        {
          return currentIndex;
        }
        else
        {
          return currentIndex + 1;
        }
      }
    }
    return textbox->text.size();
  }
  int getBlinkerStart(const DynamicTextbox* textbox,int mouseX)
  {
    int mouseXOffset = mouseX - textbox->topLeftX;
    int currentX;
    if(textbox->text.size() == 0){return 0;}
    for(int currentIndex = 0;currentIndex < textbox->text.size();currentIndex++)
    {
      int lastX = currentX;
      currentX += characterMap[textbox->text.at(currentIndex)].width * textbox->scaleX;
      if(currentX > mouseXOffset)
      {
        if(currentX - mouseXOffset > mouseXOffset - lastX)
        {
          return currentIndex;
        }
        else
        {
          return currentIndex + 1;
        }
      }
    }
    return textbox->text.size();
  }
}

#endif