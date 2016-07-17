#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Component.h"
namespace Jokengine
{
	class CircleCollider :public Component
	{
	public:
		//Radius of the collider
		GLfloat Radius;
		// Constructor(s)
		CircleCollider(std::weak_ptr<GameObject> gameObject,GLfloat radius, glm::vec2 localPosition, GLboolean isSolid);

	};
}


#endif
