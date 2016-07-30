#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Collider.h"
namespace Jokengine
{
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
