#include "Component.h"
#include"CircleCollider.h"
#include "Game.h"
#include "PhysicBody.h"

CircleCollider::CircleCollider(GameObject* owner)
	:ComponentCloneable(owner)
{
	radius = 1.0f;
}
void CircleCollider::Init()
{

	PhysicBody *ptr = owner->GetComponent<PhysicBody>();
	if (!ptr)
		ptr = owner->AddComponent<PhysicBody>();
	fixture = Game::GetInstance().GetPhysicsService().RegisterFixtureCircle(ptr->GetB2body(),this, radius*((owner->GetWorldSize().x+ owner->GetWorldSize().y)/2)/2,!isSolid,offset, physicLayer);
	fixture->SetFriction(friction);
}
