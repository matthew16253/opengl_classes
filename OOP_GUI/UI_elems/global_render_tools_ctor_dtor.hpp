<<<<<<< HEAD
#ifndef GLOBAL_RENDER_CONSTRUCTOR_DESTRUCTOR_HPP
#define GLOBAL_RENDER_CONSTRUCTOR_DESTRUCTOR_HPP

#include"../fd_decs.hpp"
#include"../charTextureGenerator/char_texture_generator.hpp"

#include<filesystem>
#include<iostream>

namespace myui
{
  GlobalRenderTools::GlobalRenderTools(float screenWidth, float screenHeight)
  {
    // INIT GFLW AND GLAD
    ResourceManager::initGLFW();
    window = ResourceManager::createWindow(screenWidth,screenHeight,false);
    ResourceManager::initGLAD();

    //  SET ALL CALLBACKS
    glfwSetMouseButtonCallback(window,mouseCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window,charCallback);

    // I AINT GOT AN IDEA WHAT THIS DOES, BUT I USED IT BEFORE
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glfwSetInputMode(window,GLFW_LOCK_KEY_MODS,GLFW_TRUE);


    //SET UP PROJECTION MATRIX
    projectionMatrix = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, 0.0f, 100.0f);

    // SET UP SHADER
    shader.generate("./UI_elems/shaders/vert_shader.glsl","./UI_elems/shaders/frag_shader.glsl");
    textShader.generate("./UI_elems/shaders/vert_text_shader.glsl","./UI_elems/shaders/frag_text_shader.glsl");

    // SET UP THE VAO AND VBO
    //
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,6*4*sizeof(float),NULL,GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0); // vertex pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float))); // texture coords
    glEnableVertexAttribArray(1);


    // SET UP THE TEXT RENDERING STUFF
    for(char currentChar = 32; currentChar < 127; currentChar++)
    {
      characterMap[currentChar] = CharacterData();
      CharTexturizer::toTexture(&(characterMap[currentChar].texture),currentChar, &(characterMap[currentChar].x));
    }
  }
}




=======
#ifndef GLOBAL_RENDER_CONSTRUCTOR_DESTRUCTOR_HPP
#define GLOBAL_RENDER_CONSTRUCTOR_DESTRUCTOR_HPP

#include"../fd_decs.hpp"
#include"../charTextureGenerator/char_texture_generator.hpp"

#include<filesystem>
#include<iostream>

namespace myui
{
  GlobalRenderTools::GlobalRenderTools(float screenWidth, float screenHeight)
  {
    // INIT GFLW AND GLAD
    ResourceManager::initGLFW();
    window = ResourceManager::createWindow(screenWidth,screenHeight,false);
    ResourceManager::initGLAD();

    //  SET ALL CALLBACKS
    glfwSetMouseButtonCallback(window,mouseCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window,charCallback);

    // I AINT GOT AN IDEA WHAT THIS DOES, BUT I USED IT BEFORE
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glfwSetInputMode(window,GLFW_LOCK_KEY_MODS,GLFW_TRUE);


    //SET UP PROJECTION MATRIX
    projectionMatrix = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, 0.0f, 100.0f);

    // SET UP SHADER
    shader.generate("./UI_elems/shaders/vert_shader.glsl","./UI_elems/shaders/frag_shader.glsl");
    textShader.generate("./UI_elems/shaders/vert_text_shader.glsl","./UI_elems/shaders/frag_text_shader.glsl");

    // SET UP THE VAO AND VBO
    //
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,6*4*sizeof(float),NULL,GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0); // vertex pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float))); // texture coords
    glEnableVertexAttribArray(1);


    // SET UP THE TEXT RENDERING STUFF
    for(char currentChar = 32; currentChar < 127; currentChar++)
    {
      characterMap[currentChar] = CharacterData();
      CharTexturizer::toTexture(&(characterMap[currentChar].texture),currentChar, &(characterMap[currentChar].x));
    }
  }
}




>>>>>>> 09b7cc8 (reinit commit)
#endif