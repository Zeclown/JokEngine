#ifndef COLLISION_H
#define COLLISION_H
#include "Collider.h"
#include "PhysicBody.h"
namespace Jokengine
{
	class Collision
	{
	public:
		Collision() {};
		Collision(Collider *colliderSelf, Collider *colliderOther, PhysicBody *physicBody ,GameObject *gameObject, std::vector<glm::vec2> contacts);
		Collider *colliderSelf;
		Collider *colliderOther;
		PhysicBody *physicBody;
		GameObject *gameObject;
		std::vector<glm::vec2> contacts;
		GLboolean trigger;
	};
}
#endif // !COLLISION_H

