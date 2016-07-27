#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Collider.h"
namespace Jokengine
{
	class CircleCollider :public ComponentCloneable<Collider,CircleCollider>
	{
	public:
		//Radius of the collider
		GLfloat radius;
		// Constructor(s)
		CircleCollider(GameObject* gameObject);

	};
}


#endif
