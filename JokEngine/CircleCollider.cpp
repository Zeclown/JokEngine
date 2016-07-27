#include "Component.h"
#include"CircleCollider.h"
#include "Game.h"
#include "PhysicBody.h"
namespace Jokengine
{
	CircleCollider::CircleCollider(GameObject* owner)
		:ComponentCloneable(owner)
	{
		radius = (owner->size.x+ owner->size.y)/2;
		PhysicBody *ptr = owner->GetComponent<PhysicBody>();
		if (!ptr)
			ptr = owner->AddComponent<PhysicBody>();
		fixture = Game::GetInstance().GetPhysicsService().RegisterFixtureCircle(ptr->GetB2body(),radius);
	}
}