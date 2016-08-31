#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"
#include <glm\glm.hpp>

//A camera component that can be registered as the current view
//
// Example:
//
//  GameObject mainCam = GameObject("CameraMain");
//  mainCam.AddComponent<Camera>();
//  Camera* camComp = Instantiate(mainCam)->GetComponent<Camera>();
//  game->GetCameraService()->RegisterCamera(*camComp);
class Camera :public ComponentCloneable<Component, Camera>
{
public:
	Camera(GameObject* gameObject);
	GLfloat zoom;
	glm::vec2 frustum;
	GLfloat farPlane;
	GLfloat nearPlane;
	glm::mat4 GetViewMatrix();




};

#endif