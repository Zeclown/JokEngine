#ifndef RAYCAST_HIT_H
#define RAYCAST_HIT_H
#include "Collider.h"

namespace Jokengine
{
	class RaycastHit
	{
		RaycastHit(Collider* collider, glm::vec2 point);
		Collider *collider;
		glm::vec2 point;
	};
}
#endif // !RAYCAST_HIT_H

