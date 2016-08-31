#ifndef RAYCAST_HIT_H
#define RAYCAST_HIT_H
#include "Collider.h"
#include "Box2D\Box2D.h"

//A raycasthit class that is often populated by the physics service
class RaycastHit
{
	public:
			
		Collider *collider;
		glm::vec2 point;
		glm::vec2 normal;
		explicit operator bool()
		{
			return collider!=nullptr;
		}
};

#endif // !RAYCAST_HIT_H

