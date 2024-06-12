#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
    public:
        unsigned int ID;
        Shader(){}
        void generate(const char* vertexPath,const char* fragmentPath)
        {
            std::string vertexCode,fragmentCode;
            std::ifstream vertexShaderFile,fragmentShaderFile;
            //allow files to throw exceptions
            vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            //read files into c strings!!   :)
            try
            {
                //std::cout<<"before shader load"<<std::endl;
                vertexShaderFile.open(vertexPath);
                //std::cout<<"after vertex load"<<std::endl;
                fragmentShaderFile.open(fragmentPath);
                //std::cout<<"after fragment load"<<std::endl;
                std::stringstream vertexShaderStream,fragmentShaderStream;
                vertexShaderStream<<vertexShaderFile.rdbuf();
                fragmentShaderStream<<fragmentShaderFile.rdbuf();
                vertexShaderFile.close();
                fragmentShaderFile.close();
                vertexCode=vertexShaderStream.str();
                fragmentCode=fragmentShaderStream.str();
            }
            catch(std::ifstream::failure e){std::cout<<"shader failed to load"<<"\n error: "<<e.what();}
            const char* vertexShaderCode=vertexCode.c_str();
            const char* fragmentShaderCode=fragmentCode.c_str();
            //compile shaders
            unsigned int vertexShader,fragmentShader;
            int vertexCompilationSuccess,fragmentCompilationSuccess,programLinkingSuccess;
            char infoLog[512];
            vertexShader=glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader,1,&vertexShaderCode,NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&vertexCompilationSuccess);

            if(!vertexCompilationSuccess)
            {
                glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
                std::cout<<"vertex shader compilation failed\n"<<infoLog<<"\n"<<vertexCode<<std::endl;
            }
            fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader,1,&fragmentShaderCode,NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&fragmentCompilationSuccess);
            if(!fragmentCompilationSuccess)
            {
                glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
                std::cout<<"fragment shader compilation failed\n"<<infoLog<<"\n"<<fragmentCode<<std::endl;
            }

            ID=glCreateProgram();
            glAttachShader(ID,vertexShader);
            glAttachShader(ID,fragmentShader);
            glLinkProgram(ID);
            glGetProgramiv(ID,GL_LINK_STATUS,&programLinkingSuccess);
            if(!programLinkingSuccess){glGetProgramInfoLog(ID,512,NULL,infoLog);std::cout<<"shader program linking failed"<<infoLog<<std::endl;}

            if(!fragmentCompilationSuccess||!vertexCompilationSuccess||!programLinkingSuccess)
            {
                throw std::invalid_argument("shaders failed to compile (please read errors and then fix)");
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }
        void use(){glUseProgram(ID);}
        //uniform functions
        //const makes it a compiler error to change member vals
        void setBool(const std::string &name,bool value)const{glUniform1i(glGetUniformLocation(ID,name.c_str()),static_cast<int>(value));}
        void setInt(const std::string &name,int value)const{glUniform1i(glGetUniformLocation(ID,name.c_str()),value);}
        void setFloat(const std::string &name,float value)const{glUniform1f(glGetUniformLocation(ID,name.c_str()),value);}
        
        void setVec2(const std::string &name,const glm::vec2 &value)const{glUniform2fv(glGetUniformLocation(ID,name.c_str()),1,&value[0]);}
        void setVec3(const std::string &name,const glm::vec3 &value)const{glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,&value[0]);}
        void setVec4(const std::string &name,const glm::vec4 &value)const{glUniform4fv(glGetUniformLocation(ID,name.c_str()),1,&value[0]);}

        void setVec2(const std::string &name,float x,float y)const{glUniform2f(glGetUniformLocation(ID,name.c_str()),x,y);}
        void setVec3(const std::string &name,float x,float y,float z)const{glUniform3f(glGetUniformLocation(ID,name.c_str()),x,y,z);}
        void setVec4(const std::string &name,float x,float y,float z,float w)const{glUniform4f(glGetUniformLocation(ID,name.c_str()),x,y,z,w);}

        void setMat2(const std::string &name,const glm::mat2 &value)const{glUniformMatrix2fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);}
        void setMat3(const std::string &name,const glm::mat3 &value)const{glUniformMatrix3fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);}
        void setMat4(const std::string &name,const glm::mat4 &value)const{glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);}

        ~Shader()
        {
            glDeleteProgram(ID);
        }
};

#endif