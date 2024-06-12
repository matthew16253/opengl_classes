#ifndef TEXT_ITEM_MANAGER_HPP
#define TEXT_ITEM_MANAGER_HPP

#include"../fd_decs.hpp"
#include"../charTextureGenerator/char_texture_generator.hpp"

namespace myui
{
    // TextItemManager::TextItemManager(DisplayRenderTools* _renderKit) : renderKit(_renderKit)
    // {
    //   for(char currentChar = 32; currentChar < 127; currentChar++)
    //   {
    //     int dimensions[2];
    //     Texture2D texture = CharTexturizer::toTexture(currentChar, dimensions);
    //     renderKit->globalRenderTools.characterMap[currentChar] = CharacterData(texture,dimensions[0],dimensions[1]);
    //   }
    // }

    void Display::renderTextItems()
    {
      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(globalRenderKit.VAO);
      glBindBuffer(GL_ARRAY_BUFFER, globalRenderKit.VBO);

      globalRenderKit.textShader.use();
      globalRenderKit.textShader.setMat4("UniformModel",modelMatrix);
      globalRenderKit.textShader.setMat4("UniformProjection",globalRenderKit.projectionMatrix);
      globalRenderKit.textShader.setInt("UniformTexture",0);

      for(auto textItemIterator = textItems.begin(); textItemIterator != textItems.end(); textItemIterator++)
      {
        if((*textItemIterator)->shouldRenderText)
        {
          float currentX = (*textItemIterator)->topleft.x + (*textItemIterator)->getTextScale() * TEXT_ITEM_TEXT_X_OFFSET;
          float y = (*textItemIterator)->topleft.y;
          float pixelHeight = (*textItemIterator)->bottomright.y - (*textItemIterator)->topleft.y;
          globalRenderKit.textShader.setVec4("UniformColor", (*textItemIterator)->textColor);
          for(auto charIndex = (*textItemIterator)->startCharRenderIndex; charIndex < (*textItemIterator)->text.size(); charIndex++)
          {
            if((*textItemIterator)->blinkerIndex == charIndex && (*textItemIterator)==lastTextItemPressed)
            {
              // RENDER BLINKER
                              float pixelWidth = (pixelHeight/globalRenderKit.characterMap['|'].y)
                                 * globalRenderKit.characterMap['|'].x * BLINKER_WIDTH_MULTIPLIER;
                              float vertices[6*4] = 
                              {
                                currentX, y, 0.0f, 0.0f,
                                currentX+pixelWidth, y, 1.0f, 0.0f,
                                currentX, y+pixelHeight, 0.0f, 1.0f,

                                currentX+pixelWidth, y, 1.0f, 0.0f,
                                currentX, y+pixelHeight, 0.0f, 1.0f,
                                currentX+pixelWidth, y+pixelHeight, 1.0f, 1.0f
                              };
                              globalRenderKit.characterMap['|'].texture.bind();
                              glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
                              glDrawArrays(GL_TRIANGLES,0,6);

                              currentX += pixelWidth;
            }
            float pixelWidth = (pixelHeight/globalRenderKit.characterMap[(*textItemIterator)->text.at(charIndex)].y)
                                 * globalRenderKit.characterMap[(*textItemIterator)->text.at(charIndex)].x;
            float vertices[6*4] = 
            {
              currentX, y, 0.0f, 0.0f,
              currentX+pixelWidth, y, 1.0f, 0.0f,
              currentX, y+pixelHeight, 0.0f, 1.0f,

              currentX+pixelWidth, y, 1.0f, 0.0f,
              currentX, y+pixelHeight, 0.0f, 1.0f,
              currentX+pixelWidth, y+pixelHeight, 1.0f, 1.0f
            };
            globalRenderKit.characterMap[(*textItemIterator)->text.at(charIndex)].texture.bind();
            glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
            glDrawArrays(GL_TRIANGLES,0,6);

            currentX += pixelWidth;
          }
          if((*textItemIterator)->blinkerIndex == (*textItemIterator)->text.size() && (*textItemIterator)==lastTextItemPressed)
          {
            // RENDER BLINKER
                            float pixelWidth = (pixelHeight/globalRenderKit.characterMap['|'].y)
                                * globalRenderKit.characterMap['|'].x * BLINKER_WIDTH_MULTIPLIER;
                            float vertices[6*4] = 
                            {
                              currentX, y, 0.0f, 0.0f,
                              currentX+pixelWidth, y, 1.0f, 0.0f,
                              currentX, y+pixelHeight, 0.0f, 1.0f,

                              currentX+pixelWidth, y, 1.0f, 0.0f,
                              currentX, y+pixelHeight, 0.0f, 1.0f,
                              currentX+pixelWidth, y+pixelHeight, 1.0f, 1.0f
                            };
                            globalRenderKit.characterMap['|'].texture.bind();
                            glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
                            glDrawArrays(GL_TRIANGLES,0,6);

                            currentX += pixelWidth;
          }
        }
      }
    }

    void defaultTextCommand(double xpos, double ypos)
    {
      // choose the blinker index
      float scale = (lastTextItemPressed->bottomright.y - lastTextItemPressed->topleft.y) / (BITMAP_IMG_HEIGHT);
      double localXpos = xpos - lastTextItemPressed->topleft.x;
      double currentX = scale * TEXT_ITEM_TEXT_X_OFFSET;
      for(int charIndex = 0; charIndex < lastTextItemPressed->text.size(); charIndex++)
      {
        double width = scale * globalRenderKit.characterMap[lastTextItemPressed->text.at(charIndex)].x;
        currentX += width;
        if(currentX > localXpos)
        {
          if(width/2 > (currentX-localXpos))
          {
            lastTextItemPressed->blinkerIndex = charIndex + 1;
          }
          else
          {
            lastTextItemPressed->blinkerIndex = charIndex;
          }
          return;
        }
      }
      currentX += scale * globalRenderKit.characterMap['|'].x;
      if(currentX > localXpos)
      {
        lastTextItemPressed->blinkerIndex = lastTextItemPressed->text.size();
      }
    }
}




#endif