#include"fd_decs.hpp"
#include<iostream>

void foo(double, double){std::cout<<"ahhh! button pressed!!!";}

int main()
{
  Texture2D t1;
  ResourceManager::getNewTexture(&t1,"C:/Users/matth/Documents/coding/cpp/OpenGL_projects/textured_box/container.jpg",false);

  myui::Display d1(true,glm::mat4(1.0f));

  //myui::Rectangle r1(&d1, glm::vec2(300,500), glm::vec2(500,300),&t1,glm::vec4(1.0,0.0,1.0,1.0),true);
  myui::Button ba1(&d1,glm::vec2(300,500),glm::vec2(500,300),&t1,glm::vec4(1.0,0.0,1.0,1.0),true,foo,true);
  myui::TextItem ti1(&d1,glm::vec2(0,0),100,myui::defaultTextCommand,true,&t1,glm::vec4(1.0,0.0,1.0,1.0),
                     true,"default_text",glm::vec4(1,1,1,1),true,true);

  while(!glfwWindowShouldClose(myui::window))
  {
    d1.renderAll();

    glClearColor(0.5,0.5,0.5,1.0);
    glfwSwapBuffers(myui::window);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
    myui::keyRepeatInputMainloop();
  }
  return 0;
}