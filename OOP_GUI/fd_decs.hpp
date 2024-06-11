#ifndef FD_DECS_HPP
#define FD_DECS_HPP

#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<opengl_classes/shaders.hpp>
#include<opengl_classes/textures.hpp>

#include"GL_class_manager.hpp"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<list>
#include<map>
#include<vector>
#include<iostream>

#define BITMAP_IMG_HEIGHT 700
#define BLINKER_WIDTH_MULTIPLIER 0.25

#define TEXT_ITEM_TEXT_X_OFFSET 100

#define DEFAULT_TEXT_SCROLL_COOLDOWN 10
#define DEFAULT_TEXT_DELAY_COOLDOWN 75

#define DEFAULT_TEXT_SCROLL_SPEED 100

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 800

namespace myui
{
  enum LongChar : short
  {
    SPACE = 32,EXCLAMATION_MARK,DOUBLE_QUOTATION,HASHTAG,DOLLAR,PERCENTAGE,AMPERSAND,
    SINGLE_QUOTATION,OPEN_PARENTHESIS,CLOSE_PARENTHESIS,ASTERISK,PLUS,COMMA,HYPHEN,
    FULL_STOP,FORWARD_SLASH,ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,COLON,
    SEMI_COLON,SMALLER_THAN,EQUALS,GREATER_THAN,QUESTION,AT,UPPER_A,UPPER_B,UPPER_C,
    UPPER_D,UPPER_E,UPPER_F,UPPER_G,UPPER_H,UPPER_I,UPPER_J,UPPER_K,UPPER_L,UPPER_M,
    UPPER_N,UPPER_O,UPPER_P,UPPER_Q,UPPER_R,UPPER_S,UPPER_T,UPPER_U,UPPER_V,UPPER_W,
    UPPER_X,UPPER_Y,UPPER_Z,OPEN_SQUARE_BRACKET,BACK_SLASH,CLOSE_SQUARE_PARENTHESIS,
    POWER,UNDERSCORE,GRAVE_ACCENT,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,
    Z,OPEN_CURLY_BRACE,VERTICAL_BAR,CLOSING_CURLY_BRACE,TILDE

    //continue here
  };
  typedef std::vector<LongChar> LongString;




  class Display;
  class GlobalUIManager;
  class GlobalRenderTools;
  class GlobalPerformanceAndState;

  class Area;
  class Button;
  class Rectangle;
  class TextItem;





  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void mouseCallback(GLFWwindow* window, int button, int action, int mods);
  void charCallback(GLFWwindow* window, unsigned int codepoint);






  class CharacterData
  {
    public:
      Texture2D texture;
      int x,y;
      CharacterData(Texture2D _texture, int _x, int _y) : texture(_texture), x(_x), y(_y)  {}
      CharacterData(){}
  };


// HERE ARE ALL THE BASIC UI ELEMENT CLASSES

  class Area
  {
    protected:
      glm::vec2 topleft, bottomright;
    public:
      //Area(){}
      Area(Display* creator, const glm::vec2 topleft, const glm::vec2 bottomright);
      virtual ~Area(){}
      friend class Display;
      friend void defaultTextCommand(double xpos,double ypos);
  }; 
  class Rectangle : public Area
  {
    protected:
      Texture2D* texture;
      glm::vec4 color;
      bool shouldRender;
    public:
      //Rectangle(){}
      Rectangle(Display* creator, glm::vec2 _topleft, glm::vec2 _bottomright, Texture2D* _texture, const glm::vec4& _color, bool _shouldRender);
      ~Rectangle() override {};
      friend class Display;
      friend void defaultTextCommand(double xpos,double ypos);
  };
  class Button : public Rectangle
  {
    protected:
	    void(*command)(double,double);
      bool buttonEnabled;
	  public:
      //Button(){}
      Button(Display* creator, const glm::vec2 _topleft, const glm::vec2 _bottomright, Texture2D* _texture,
       glm::vec4 _color, bool shouldRender, void(*command)(double,double), bool buttonEnabled);
      ~Button() override {};
      friend class Display;
      friend void defaultTextCommand(double xpos,double ypos);
 };
  class TextItem : public Button
  {
    protected:
      std::string text;
      glm::vec4 textColor;
      int blinkerIndex, startCharRenderIndex;
      bool shouldRenderText, canWriteTo;

    public:
      //TextItem(){}
      TextItem(Display* creator, const glm::vec2 _topleft, int height,
       void(*_command)(double,double), bool _buttonEnabled, Texture2D* _texture, glm::vec4 _color,
       bool _shouldRender, const std::string& _text, const glm::vec4 _textColor, bool _shouldRenderText,
       bool _canWriteTo);
      ~TextItem() override {};
      void tryAddText(char newChar);
      void tryRemoveText();
      void tryMoveBlinker(int change);
      double getTextWidth();
      double getTextWidth(const std::string& text, int height);
      double getTextScale();
      friend class Display;
      friend void defaultTextCommand(double xpos,double ypos);
  };

// HERE ARE THE MORE COMPLEX AND DETAILED UI ELEMENT CLASSES

  class Display
  {
    private:
      bool active;
    
      glm::mat4 modelMatrix;


      std::list<Area*> areas;
      std::list<Rectangle*> rectangles;
      std::list<Button*> buttonAreas;
      std::list<TextItem*> textItems;

    public:
      friend class Area;
      friend class Rectangle;
      friend class Button;
      friend class TextItem;
      friend void mouseCallback(GLFWwindow* window, int button, int action, int mods);

      Display(bool _active, const glm::mat4& _modelMatrix);

      void renderRectangles();
      
      void checkButtonClicks(double xpos, double ypos);

      void renderTextItems();

      void renderAll();

      inline void use(){active=true;}
      inline void disable(){active=false;}

  };


  class GlobalUIManager
  {
    private:
      std::list<Display*> displays;
      glm::vec4 screenColor;
    public:
      friend class Display;
      friend void mouseCallback(GLFWwindow* window, int button, int action, int mods);
      void setScreenColor(const glm::vec4 _screenColor){screenColor = _screenColor;}
      glm::vec4 getScreenColor(){return screenColor;}
  };




  class GlobalRenderTools
  {
    private:
      glm::mat4 projectionMatrix;
      std::map<char,CharacterData> characterMap;
      unsigned int VAO, VBO;
      Shader shader;
      Shader textShader;
    public:
      friend class Display;
      friend class TextItem;
      GlobalRenderTools(float screenWidth, float screenHeight);
      friend void defaultTextCommand(double xpos, double ypos);
  };

  class GlobalPerformanceAndState
  {
    private:
      double deltaTime,lastFrameTime;
      double currentTextScrollCooldown;
      int lastKeyPressed;
      bool firstKeyJustPressed = false;
      bool shouldWaitForFirstKey = true;
    public:
      GlobalPerformanceAndState() : currentTextScrollCooldown(DEFAULT_TEXT_SCROLL_COOLDOWN)  {}
      void updateDeltaTime()
      {
        deltaTime = glfwGetTime() - lastFrameTime;
        lastFrameTime=glfwGetTime();
      }
      void keyReleased()
      {
        firstKeyJustPressed = true;
        currentTextScrollCooldown = 0;
      }
      bool keyPressed(int pressed)
      {
        bool returnValue = false;
        currentTextScrollCooldown -= DEFAULT_TEXT_SCROLL_SPEED * deltaTime;
        std::cout<<currentTextScrollCooldown<<"\n";
        if(pressed != lastKeyPressed)
        {
          lastKeyPressed = pressed;
          keyReleased();
        }
        if(currentTextScrollCooldown <= 0)
        {
          currentTextScrollCooldown = DEFAULT_TEXT_SCROLL_COOLDOWN;
          if(firstKeyJustPressed)
          {
            currentTextScrollCooldown = DEFAULT_TEXT_DELAY_COOLDOWN;
            firstKeyJustPressed = false;
          }
          returnValue = true;
        }
        return returnValue;
      }
  };



  GlobalUIManager UIManager;

  GlobalRenderTools globalRenderKit(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  GlobalPerformanceAndState globalPerformanceAndState;

  Button* lastButtonPressed;
  TextItem* lastTextItemPressed;

  GLFWwindow* window;



}



#include"UI_elems/Area.hpp"
#include"UI_elems/button.hpp"
#include"UI_elems/button_manager.hpp"
#include"UI_elems/display_ctor_and_render_all.hpp"
#include"UI_elems/general_helpers.hpp"
#include"UI_elems/general_helpers.hpp"
#include"UI_elems/global_render_tools_ctor_dtor.hpp"
#include"UI_elems/key_callbacks.hpp"
#include"UI_elems/rectangle.hpp"
#include"UI_elems/rectangle_manager.hpp"
#include"UI_elems/text_item.hpp"
#include"UI_elems/text_item_manager.hpp"
#include"charTextureGenerator/char_texture_generator.hpp"


#endif