#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Collider.h"
namespace Jokengine
{
	//BoxCollider Component
	//Add a boxlike shape to the gameobject that collides with other colliders
	//Will add a physicbody component if none is currently on the gameobject
	class BoxCollider :public ComponentCloneable<Collider, BoxCollider>
	{
	public:
		//Radius of the collider
		glm::vec2 size;
		// Constructor(s)
		BoxCollider(GameObject* gameObject);
	protected:
		virtual void Init();

	};
}


#endif
