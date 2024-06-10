<<<<<<< HEAD
#ifndef TEXT_ITEM_HPP
#define TEXT_ITEM_HPP

#include"../fd_decs.hpp"

namespace myui
{
  TextItem::TextItem(Display* creator, const glm::vec2 _topleft, int _height,
   void(*_command)(double,double), bool _buttonEnabled, Texture2D* _texture, glm::vec4 _color,
   bool _shouldRender, const std::string& _text, const glm::vec4 _textColor, bool _shouldRenderText,
    bool _canWriteTo)
   : text(_text), textColor(_textColor), blinkerIndex(0), startCharRenderIndex(0), shouldRenderText(_shouldRenderText),
    canWriteTo(_canWriteTo), 
    Button(creator,_topleft,glm::vec2(getTextWidth(_text,_height),_height),_texture,_color,_shouldRender,_command,_buttonEnabled)
  {
    creator->textItems.push_back(this);
  }

  void TextItem::tryAddText(char newChar)
  {
    if(canWriteTo)
    {
      text.insert(text.begin()+blinkerIndex,newChar);
      bottomright.x += globalRenderKit.characterMap.at(newChar).x * getTextScale();
      blinkerIndex++;
    }
  }
  void TextItem::tryRemoveText()
  {
    if(canWriteTo && blinkerIndex != 0)
    {
      bottomright.x -= globalRenderKit.characterMap.at(text.at(blinkerIndex-1)).x * getTextScale();
      text.erase(text.begin()+blinkerIndex-1);
      tryMoveBlinker(-1);
    }
  }
  void TextItem::tryMoveBlinker(int change)
  {
    constrainedChange<int>(blinkerIndex,change,0,text.size());
  }
  double TextItem::getTextWidth()
  {
    double currentWidth = 0;
    double scale = (topleft.y-bottomright.y) / BITMAP_IMG_HEIGHT;
    for(int charIndex = 0; charIndex < text.size(); charIndex++)
    {
      currentWidth += globalRenderKit.characterMap.at(text.at(charIndex)).x  *  scale;
    }
    return currentWidth + 2 * TEXT_ITEM_TEXT_X_OFFSET * scale;
  }
  double TextItem::getTextWidth(const std::string& inputText,int height)
  {
    double currentWidth = 0;
    double scale = (static_cast<double>(height)) / BITMAP_IMG_HEIGHT;
    for(int charIndex = 0; charIndex < inputText.size(); charIndex++)
    {
      currentWidth += globalRenderKit.characterMap.at(inputText.at(charIndex)).x  *  scale;
    }
    return currentWidth + 2 * TEXT_ITEM_TEXT_X_OFFSET * scale;
  }
  inline double TextItem::getTextScale()
  {
    return (bottomright.y-topleft.y)  /  BITMAP_IMG_HEIGHT;
  }
}



=======
#ifndef TEXT_ITEM_HPP
#define TEXT_ITEM_HPP

#include"../fd_decs.hpp"

namespace myui
{
  TextItem::TextItem(Display* creator, const glm::vec2 _topleft, int _height,
   void(*_command)(double,double), bool _buttonEnabled, Texture2D* _texture, glm::vec4 _color,
   bool _shouldRender, const std::string& _text, const glm::vec4 _textColor, bool _shouldRenderText,
    bool _canWriteTo)
   : text(_text), textColor(_textColor), blinkerIndex(0), startCharRenderIndex(0), shouldRenderText(_shouldRenderText),
    canWriteTo(_canWriteTo), 
    Button(creator,_topleft,glm::vec2(getTextWidth(_text,_height),_height),_texture,_color,_shouldRender,_command,_buttonEnabled)
  {
    creator->textItems.push_back(this);
  }

  void TextItem::tryAddText(char newChar)
  {
    if(canWriteTo)
    {
      text.insert(text.begin()+blinkerIndex,newChar);
      bottomright.x += globalRenderKit.characterMap.at(newChar).x * getTextScale();
      blinkerIndex++;
    }
  }
  void TextItem::tryRemoveText()
  {
    if(canWriteTo && blinkerIndex != 0)
    {
      bottomright.x -= globalRenderKit.characterMap.at(text.at(blinkerIndex-1)).x * getTextScale();
      text.erase(text.begin()+blinkerIndex-1);
      tryMoveBlinker(-1);
    }
  }
  void TextItem::tryMoveBlinker(int change)
  {
    constrainedChange<int>(blinkerIndex,change,0,text.size());
  }
  double TextItem::getTextWidth()
  {
    double currentWidth = 0;
    double scale = (topleft.y-bottomright.y) / BITMAP_IMG_HEIGHT;
    for(int charIndex = 0; charIndex < text.size(); charIndex++)
    {
      currentWidth += globalRenderKit.characterMap.at(text.at(charIndex)).x  *  scale;
    }
    return currentWidth + 2 * TEXT_ITEM_TEXT_X_OFFSET * scale;
  }
  double TextItem::getTextWidth(const std::string& inputText,int height)
  {
    double currentWidth = 0;
    double scale = (static_cast<double>(height)) / BITMAP_IMG_HEIGHT;
    for(int charIndex = 0; charIndex < inputText.size(); charIndex++)
    {
      currentWidth += globalRenderKit.characterMap.at(inputText.at(charIndex)).x  *  scale;
    }
    return currentWidth + 2 * TEXT_ITEM_TEXT_X_OFFSET * scale;
  }
  inline double TextItem::getTextScale()
  {
    return (bottomright.y-topleft.y)  /  BITMAP_IMG_HEIGHT;
  }
}



>>>>>>> 09b7cc8 (reinit commit)
#endif