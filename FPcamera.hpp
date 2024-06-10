#ifndef PF_CAMERA
#define PF_CAMERA

//#include<iostream>

#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define DEFAULT_YAW -90.0f                            // Use macros for default constructor args
#define DEFAULT_PITCH 0.0f
#define DEFAULT_ZOOM 45.0f
#define DEFAULT_SENS 2.0f
#define DEFAULT_SPEED 1.0f
#define WORLD_UP glm::vec3(0.0f,1.0f,0.0f)
#define DEFAULT_CAM_POS glm::vec3(0.0f,0.0f,0.0f)

enum camDirections{FORWARD,BACKWARDS,LEFT,RIGHT,UP,DOWN};
enum constraints{PITCH,YAW,ZOOM,X,Y,Z};
struct constraint{bool isConstraining;float maxConstraint;float minConstraint;};

class FPCamera
{
  private:
    void updateDirectionVecs()
    {
      glm::vec3 newFront;
      newFront.x=cos(glm::radians(camYaw))*cos(glm::radians(camPitch));
      newFront.y=sin(glm::radians(camPitch));
      newFront.z=sin(glm::radians(camYaw))*cos(glm::radians(camPitch));
      camFront=newFront;
      camRight=glm::normalize(glm::cross(newFront,worldUp));
      camUp=glm::normalize(glm::cross(camRight,camFront));
    }
  public:
    float camPitch,camYaw,camMovementSpeed,camSensitivity,camZoom;
    //double lastX,lastY;
    glm::vec3 camFront,camRight,camUp,camPos,worldUp;
    constraint camPitchConstraint = constraint{true,89.0f,-89.0f};
    constraint camYawConstraint = constraint{false,0.0f,0.0f};
    constraint camZoomConstraint = constraint{false,0.0f,0.0f};
    constraint camXConstraint = constraint{false,0.0f,0.0f};
    constraint camYConstraint = constraint{false,0.0f,0.0f};
    constraint camZConstraint = constraint{false,0.0f,0.0f};
    void setConstraint(constraints constraintType,bool isConstraining=false,float maxConstraint=0.0f,float minConstraint=0.0f)
    {
      if(constraintType==PITCH){camPitchConstraint.isConstraining=isConstraining;camPitchConstraint.maxConstraint=maxConstraint;camPitchConstraint.minConstraint=minConstraint;}
      else if(constraintType==YAW){camYawConstraint.isConstraining=isConstraining;camYawConstraint.maxConstraint=maxConstraint;camYawConstraint.minConstraint=minConstraint;}
      else if(constraintType==ZOOM){camZoomConstraint.isConstraining=isConstraining;camZoomConstraint.maxConstraint=maxConstraint;camZoomConstraint.minConstraint=minConstraint;}
      else if(constraintType==X){camXConstraint.isConstraining=isConstraining;camXConstraint.maxConstraint=maxConstraint;camXConstraint.minConstraint=minConstraint;}
      else if(constraintType==Y){camYConstraint.isConstraining=isConstraining;camYConstraint.maxConstraint=maxConstraint;camYConstraint.minConstraint=minConstraint;}
      else if(constraintType==Z){camZConstraint.isConstraining=isConstraining;camZConstraint.maxConstraint=maxConstraint;camZConstraint.minConstraint=minConstraint;}
    }
    FPCamera(glm::vec3 initPos,float initYaw,float initPitch,float initZoom,float speed,float sens)
    :camPos(initPos),camYaw(initYaw),camPitch(initPitch),camZoom(initZoom),camMovementSpeed(speed),
    camSensitivity(sens),worldUp(WORLD_UP),camUp(WORLD_UP){updateDirectionVecs();}
    glm::mat4 getLookAt(){return glm::lookAt(camPos,camPos+camFront,camUp);}
    void processKeyboardMovement(camDirections currentDirection,float deltaTime)
    {
      //key moves
      if(currentDirection==FORWARD){camPos+=camFront*camMovementSpeed*deltaTime;}else if(currentDirection==BACKWARDS){camPos-=camFront*camMovementSpeed*deltaTime;}
      else if(currentDirection==LEFT){camPos-=camRight*camMovementSpeed*deltaTime;}else if(currentDirection==RIGHT){camPos+=camRight*camMovementSpeed*deltaTime;}
      else if(currentDirection==UP){camPos+=camUp*camMovementSpeed*deltaTime;}else if(currentDirection==DOWN){camPos-=camUp*camMovementSpeed*deltaTime;}
      //constrain checks
      if(camZConstraint.isConstraining){if(camPos.z>camZConstraint.maxConstraint){camPos.z=camZConstraint.maxConstraint;}else if(camPos.z<camZConstraint.minConstraint){camPos.z=camZConstraint.minConstraint;}}
      if(camYConstraint.isConstraining){if(camPos.z>camYConstraint.maxConstraint){camPos.z=camYConstraint.maxConstraint;}else if(camPos.z<camYConstraint.minConstraint){camPos.z=camYConstraint.minConstraint;}}
      if(camXConstraint.isConstraining){if(camPos.z>camXConstraint.maxConstraint){camPos.z=camXConstraint.maxConstraint;}else if(camPos.z<camXConstraint.minConstraint){camPos.z=camXConstraint.minConstraint;}}
    }
    void processMouseMovement(float yOffset,float xOffset,float deltaTime)
    {
      camPitch+=deltaTime*camSensitivity*yOffset;camYaw+=deltaTime*camSensitivity*xOffset;
      if(camPitchConstraint.isConstraining){if(camPitch>camPitchConstraint.maxConstraint){camPitch=camPitchConstraint.maxConstraint;}else if(camPitch<camPitchConstraint.minConstraint){camPitch=camPitchConstraint.minConstraint;}}
      updateDirectionVecs();
    }
    void processMouseScroll(float yOffset)
    {camZoom+=yOffset;if(camZoomConstraint.isConstraining){if(camZoom>camZoomConstraint.maxConstraint){camZoom=camZoomConstraint.maxConstraint;}else if(camZoom<camZConstraint.minConstraint){camZoom=camZoomConstraint.minConstraint;}}}
    //continue;
    //void setLastCamPos(double x, double y){lastX=x;lastY=y;}
};
#endif