#include "Collision.h"
namespace Jokengine
{
	Collision::Collision(Collider *colliderSelf, Collider *colliderOther, PhysicBody *physicBody, GameObject *gameObject, std::vector<glm::vec2> contacts)
	: colliderSelf(colliderSelf),colliderOther(colliderOther),physicBody(physicBody),gameObject(gameObject),contacts(contacts)
	{

	}
}