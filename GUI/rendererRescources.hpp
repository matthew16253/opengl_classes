#ifndef COMMON_RENDERER_RESOURCES
#define COMMON_RENDERER_RESOURCES

#include<list>
#include<string>
#include<map>

#include<opengl_classes/textures.hpp>
#include<opengl_classes/shaders.hpp>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//enums
enum rectanglePoint{BOTTOMLEFT,BOTTOMRIGHT,TOPLEFT,TOPRIGHT,CENTER};


namespace myui
{
  class Display;
  //please take note that any button structs'toplefttranslate is only visual.  in euclidean coord form they would be bottomleft
  //button structs
  class TexturedButton
  {
    public:
      Texture2D* texture;glm::vec2 topLeftTranslate;glm::vec2 scale;bool shouldRender;bool enabled;void(*command)();
      TexturedButton(Texture2D* t_texture,glm::vec2 t_topLeftTranslate,glm::vec2 t_scale,bool t_shouldRender,bool t_enabled,void(*t_command)());
  };
  class ColoredButton
  {
    public:
      glm::vec4 color;glm::vec2 topLeftTranslate;glm::vec2 scale;bool shouldRender;bool enabled;void(*command)();
      ColoredButton(glm::vec4 t_color,glm::vec2 t_topLeftTranslate,glm::vec2 t_scale,bool t_shouldRender,bool t_enabled,void(*t_command)());
  };
  class CustomButton
  {
    public:
      Texture2D* texture;glm::vec4 color;glm::vec2 topLeftTranslate;glm::vec2 scale;bool shouldRender;bool enabled;void(*command)();
      CustomButton(Texture2D* t_texture,glm::vec4 t_color,glm::vec2 t_topLeftTranslate,glm::vec2 t_scale,bool t_shouldRender,bool t_enabled,void(*t_command)());
  };
  // textbox stuff
  class FixedTextbox
  {
    public:
      std::string text;glm::vec4 color;glm::vec4 bgcolor;float scaleX;float scaleY;int topLeftX;int topLeftY;int widthLimit;bool shouldRender;int startChar;bool canWriteTo;int blinkerStart;
      FixedTextbox(std::string t_text,glm::vec4 t_color,glm::vec4 t_bgcolor,float t_scaleX,float t_scaleY,int t_topLeftX,int t_topLeftY,int t_widthLimit,bool t_shouldRender,int t_startChar,bool t_canWriteTo,int t_blinkerStart);
  };
  class DynamicTextbox
  {
    public:
      std::string text;glm::vec4 color;glm::vec4 bgcolor;float scaleX;float scaleY;int topLeftX;int topLeftY;int width;bool shouldRender;int blinkerStart;bool canWriteTo;
      DynamicTextbox(std::string t_text,glm::vec4 t_color,glm::vec4 t_bgcolor,float t_scaleX,float t_scaleY,int t_topLeftX,int t_topLeftY,int t_width,bool t_shouldRender,bool t_canWriteTo,int t_blinkerStart);
  };

  struct characterData{Texture2D* texture;int width;int height;};


  std::map<char,characterData> characterMap;

  unsigned int rectangleVAO;
  Shader* customRectangleShader = nullptr;
  Shader* coloredRectangleShader = nullptr;
  Shader* texturedRectangleShader = nullptr;



  unsigned int textVBO,textVAO;
  Shader* textShader = nullptr;

  unsigned int textbgVBO,textbgVAO;
  Shader* textbgShader = nullptr;
  
  FixedTextbox* selectedFixedTextbox;
  DynamicTextbox* selectedDynamicTextbox;



  std::list<Display*> displayList;

  Display* getNewDisplay();

  void initRectangleRenderer();
  void initTextRenderer();



  Display* currentDisplay = nullptr;



  int textboxScrollSpeed = 5;
  int textboxScrollCountdown = textboxScrollSpeed;
  double deltaTime = 0;
  double lastFrameTime = glfwGetTime();



  int getPixelWidth(const std::string& text,float scaleX);
  int getPixelHeight(float scaleY);
  template<typename T>void tryIncrement(T& value,T increment,T lowerLimit,T upperLimit);
  template<typename T>void tryLowerBoundedIncrement(T& value,T increment,T lowerLimit);
  template<typename T>void tryUpperBoundedIncrement(T& value,T increment,T upperLimit);
  int getBlinkerStart(const FixedTextbox* textbox,int mouseX);
  int getBlinkerStart(const DynamicTextbox* textbox,int mouseX);

  void changeCurrentDisplay(Display* t_display);
  void tryEditTextboxes(int codepoint);
  void checkTextboxClicks(int mouseX,int mouseY);
  void checkButtonClicks(int mouseX,int mouseY);
  void checkClicks(int mouseX,int mouseY);
  void tryScrollTextboxes(GLFWwindow* window);

  void destroyResources();


  class Display
  {  
    public:
      std::list<FixedTextbox*> fixedTextBoxList;
      std::list<DynamicTextbox*> dynamicTextBoxList;

      std::list<TexturedButton*> texturedButtonList;
      std::list<ColoredButton*> coloredButtonList;
      std::list<CustomButton*> customButtonList;



      // projection matrix
      glm::mat4 projection;

      // model matrix
      glm::mat4 model;

      //screen color
      glm::vec4 screenColor;

      //forward definitions
      TexturedButton* getNewTexturedButton(Texture2D* texture,rectanglePoint point,glm::vec2 pos,glm::vec2 size,void(*command)());
      TexturedButton* getNewTexturedButton(Texture2D* texture,rectanglePoint point1,glm::vec2 pos1,rectanglePoint point2,glm::vec2 pos2,void(*command)());
      ColoredButton* getNewColoredButton(glm::vec4 color,rectanglePoint point,glm::vec2 pos,glm::vec2 size,void(*command)());
      ColoredButton* getNewColoredButton(glm::vec4 color,rectanglePoint point1,glm::vec2 pos1,rectanglePoint point2,glm::vec2 pos2,void(*command)());
      CustomButton* getNewCustomButton(Texture2D* texture,glm::vec4 color,rectanglePoint point,glm::vec2 pos,glm::vec2 size,void(*command)());
      CustomButton* getNewCustomButton(Texture2D* texture,glm::vec4 color,rectanglePoint point1,glm::vec2 pos1,rectanglePoint point2,glm::vec2 pos2,void(*command)());
      void renderAllButtons(bool renderTextured,bool renderColored,bool renderCustom);
      void deleteButton(ColoredButton* button);
      void deleteButton(TexturedButton* button);
      void deleteButton(CustomButton* button);
      void deleteAllButtons(bool deleteTextured,bool deleteColored,bool deleteCustom);
      void checkButtonClicksCallback(bool checkTextured,bool checkColored,bool checkCustom,double xpos,double ypos);
      FixedTextbox* getNewFixedTextbox(const std::string& text,glm::vec4 textColor,glm::vec4 bgColor,glm::vec2 textScale,glm::ivec2 topLeft,int widthLimit,bool canWriteTo);
      DynamicTextbox* getNewDynamicTextbox(const std::string& text,glm::vec4 textColor,glm::vec4 bgColor,glm::vec2 textScale,glm::ivec2 topLeft,bool canWriteTo);
      void changeText(FixedTextbox* textbox,const std::string& newText);
      void changeText(DynamicTextbox* textbox,const std::string& newText);
      void addText(FixedTextbox* textbox,const std::string& newText);
      void addText(DynamicTextbox* textbox,const std::string& newText);
      void addText(FixedTextbox* textbox,char newText,int index);
      void addText(DynamicTextbox* textbox,char newText,int index);
      void removeText(FixedTextbox* textbox,int index);
      void removeText(DynamicTextbox* textbox,int index);
      void prepareTextboxRender();
      void renderFixedTextbox(FixedTextbox* textbox);
      void renderDynamicTextbox(DynamicTextbox* textbox);
      void renderAllTextboxes(bool renderFixed,bool renderDynamic);
      void deleteAllTextboxes(bool deleteDynamic,bool deleteFixed);
      void deleteTextbox(DynamicTextbox* textbox);
      void deleteTextbox(FixedTextbox* textbox);
      void checkTextboxClicksCallback(double xpos,double ypos);
      void tryMoveTextboxCallback(int change);
      void removeTextCallback();
      void tryAddTextCallback(char newText);
      void prepareCharacterRender();
      void renderCharacter(char text,const glm::vec2& scale,const glm::ivec2& topleft);

      //change the projection matrix
      void changeProjection(float width,float height)
      {
        projection = glm::ortho(0.0f,width,height,0.0f,0.0f,100.0f);
      }
      void changeModel(const glm::mat4& t_model)
      {
        model = t_model;
      }

      //          DELETE ALL RESOURCES ASSOCIATED WITH THE RECTANGLE RENDERER also please redo this to a destructor
      ~Display()
      {
        deleteAllButtons(true,true,true);
        deleteAllTextboxes(true,true);
        destroyResources();
      }
  };





  template<typename T>void tryIncrement(T& value,T increment,T lowerLimit,T upperLimit)
  {
    value += increment;
    if(lowerLimit > value){value=lowerLimit;}
    else if(upperLimit < value){value = upperLimit;}
  }
  template<typename T>void tryLowerBoundedIncrement(T& value,T increment,T lowerLimit)
  {
    value += increment;
    if(lowerLimit > value){value=lowerLimit;}
  }
  template<typename T>void tryUpperBoundedIncrement(T& value,T increment,T upperLimit)
  {
    value += increment;
    if(upperLimit < value){value = upperLimit;}
  }
  int getPixelWidth(const std::string& text,float scaleX)
  {
    float x = 0;
    for(auto it = text.begin();it!=text.end();it++)
    {
      std::cout<<*it<<" width: "<<characterMap[*it].width<<"scale:"<<scaleX<<std::endl;
      x += characterMap[*it].width * scaleX;
    }
    std::cout<<"width of new textbox string"<<text<<"  "<<x<<std::endl;
    return x;
  }
  int getPixelHeight(float scaleY)
  {
    return 700.0f*scaleY;
  }
  void destroyResources()
  {
    delete textShader;
    delete customRectangleShader;
    delete coloredRectangleShader;
    delete texturedRectangleShader;
    for(auto it = characterMap.begin();it != characterMap.end();it++)
    {
      delete (*it).second.texture;
    }
    for(auto it = displayList.begin();it != displayList.end();it++)
    {
      delete *it;
    }
  }
  Display* getNewDisplay()
  {
    Display* newDisplay = new Display();
    displayList.push_back(newDisplay);
    return newDisplay;
  }
  void changeCurrentDisplay(Display* t_display)
  {
    currentDisplay = t_display;
  }
};

#endif