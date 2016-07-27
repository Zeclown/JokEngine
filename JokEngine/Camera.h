#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"
#include <glm\glm.hpp>
namespace Jokengine
{
	//default camera value
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
}
#endif