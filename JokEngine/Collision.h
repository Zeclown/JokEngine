#ifndef COLLISION_H
#define COLLISION_H
#include "Collider.h"
#include "PhysicBody.h"
namespace Jokengine
{
	//A basic collision class
	//used by collision callback functions
	//Contains collision data recovered from Box2D
	class Collision
	{
	public:
		Collision() {};
		Collision(Collider *colliderSelf, Collider *colliderOther, PhysicBody *physicBody ,GameObject *gameObject, std::vector<glm::vec2> contacts,GLboolean sensor=false);
		Collider *colliderSelf;
		Collider *colliderOther;
		PhysicBody *physicBody;
		GameObject *gameObject;
		std::vector<glm::vec2> contacts;
		GLboolean sensor;
	};
}
#endif // !COLLISION_H

