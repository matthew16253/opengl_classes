#ifndef CHAR_TEXTURE_GENERATOR
#define CHAR_TEXTURE_GENERATOR


#include<glad/glad.h>
#include<glfw/glfw3.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#endif

#include<opengl_classes/textures.hpp>
#include"../GL_class_manager.hpp"

#include<iostream>
#include<string>

namespace CharTexturizer
{
  void toTexture(Texture2D* location,char myCharacter,int imageDimensions[2])
  {
    std::cout<<"-"<<(int)myCharacter<<"-"<<std::endl;
    std::string folder = "./charTextureGenerator/bitmaps/";
    std::string filename;
    if(myCharacter < 32 || myCharacter == 128){throw std::runtime_error("unexpected character in first 31 ASCII chars (inclusive): " + myCharacter);}
    if(48<=myCharacter && myCharacter<=57)
    {
      filename = std::string{myCharacter} + ".png";
    }
    else
    {
      std::cout<<(int)myCharacter<<std::endl;
      switch(myCharacter)
      {
        case ' ':{filename = "space.png";break;}
        case '.':{filename = "fullstop.png";break;}
        case '>':{filename = "greaterthan.png";break;}
        case '<':{filename = "lessthan.png";break;}
        case '/':{filename = "forwardslash.png";break;}
        case 92:{filename = "backslash.png";break;}
        case '|':{filename = "pipe.png";break;}
        case '?':{filename = "questionmark.png";break;}
        case '#':{filename = "hashtag.png";break;}
        case '%':{filename = "percent.png";break;}
        case '&':{filename = "ampersand.png";break;}
        case '{':{filename = "opencurlybracket.png";break;}
        case '}':{filename = "closecurlybracket.png";break;}
        case '[':{filename = "opensquarebracket.png";break;}
        case ']':{filename = "closesquarebracket.png";break;}
        case '(':{filename = "openbracket.png";break;}
        case ')':{filename = "closebracket.png";break;}
        case '*':{filename = "asterisk.png";break;}
        case '$':{filename = "dollar.png";break;}
        case '!':{filename = "exclamationmark.png";break;}
        case 39:{filename = "singlequote.png";break;}
        case '"':{filename = "doublequote.png";break;}
        case ':':{filename = "colon.png";break;}
        case '@':{filename = "at.png";break;}
        case '+':{filename = "plus.png";break;}
        case 96:{filename = "backtick.png";break;}
        case '=':{filename = "=.png";break;}
        case '^':{filename = "power.png";break;}
        case ',':{filename = ",.png";break;}
        case '-':{filename = "-.png";break;}
        case '~':{filename = "tilda.png";break;}
        case ';':{filename = ";.png";break;}
        case '_':{filename = "_.png";break;}
        default:{filename = (isupper(myCharacter)?"u":"l")+std::string{(char)toupper(myCharacter)};filename+=".png";}
      }
    }
    // Texture2D* charTexture = new Texture2D();
    // charTexture->generate(folder+filename,GL_LINEAR,GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR,GL_RGBA,GL_RGBA,true,imageDimensions);
    ResourceManager::getCustomTexture(location,folder+filename,GL_LINEAR,GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,GL_LINEAR,GL_RED,GL_RGBA,imageDimensions);
  }
};


#endif