#include "RaycastHit.h"
namespace Jokengine
{
	RaycastHit::RaycastHit(Collider* collider, glm::vec2 point)
		:collider(collider),point(point)
	{

	}
}