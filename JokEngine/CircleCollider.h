#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Collider.h"
namespace Jokengine
{
	//CircleCollider Component
	//Add a circlelike shape to the gameobject that collides with other colliders
	//Will add a physicbody component if none is currently on the gameobject
	class CircleCollider :public ComponentCloneable<Collider,CircleCollider>
	{
	public:
		//Radius of the collider
		GLfloat radius;
		// Constructor(s)
		CircleCollider(GameObject* gameObject);
	protected:
		virtual void Init();

	};
}


#endif
