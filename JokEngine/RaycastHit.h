#ifndef RAYCAST_HIT_H
#define RAYCAST_HIT_H
#include "Collider.h"

namespace Jokengine
{
	class RaycastHit : public b2RayCastCallback
	{
		public:
			
			Collider *collider;
			glm::vec2 point;
			glm::vec2 normal;
			explicit operator bool()
			{
				return collider!=NULL_PTR;
			}
	};
}
#endif // !RAYCAST_HIT_H

