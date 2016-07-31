#include "BoxCollider.h"
#include "GameObject.h"
#include "PhysicBody.h"
#include "Game.h"
namespace Jokengine
{
	BoxCollider::BoxCollider(GameObject *owner)
		:ComponentCloneable(owner)
	{
		size = owner->size;
	}
	void BoxCollider::Init()
	{
		PhysicBody *ptr = owner->GetComponent<PhysicBody>();
		if (!ptr)
			ptr = owner->AddComponent<PhysicBody>();
		fixture = Game::GetInstance().GetPhysicsService().RegisterFixtureBox(ptr->GetB2body(),this,size,offset);
	}

}