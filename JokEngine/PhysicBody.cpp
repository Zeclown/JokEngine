#include "PhysicBody.h"
#include "Game.h"
#include "Box2D\Dynamics\b2Body.h"
namespace Jokengine
{
	PhysicBody::PhysicBody(GameObject* gameObject)
		:velocity(glm::vec2(0, 0)), velocityModifier(glm::vec2(1, 1)), freezeRotation(false), kinematic(false)
		, centerOfMass(glm::vec2(0, 0)), drag(0.0f), angularDrag(0.0f), gravity(true), interpolate(false), mass(1), angularVelocity(0,0), rBody(nullptr), ComponentCloneable(gameObject)
	{
	}
	PhysicBody::PhysicBody(PhysicBody const & pb)
		: ComponentCloneable(pb), velocity(pb.velocity), velocityModifier(pb.velocityModifier), freezeRotation(pb.freezeRotation), kinematic(pb.kinematic)
		, centerOfMass(pb.centerOfMass), drag(pb.drag), angularDrag(pb.angularDrag), gravity(pb.gravity), interpolate(pb.interpolate), mass(pb.mass), angularVelocity(pb.angularVelocity), rBody(nullptr)
	{

	}
	void PhysicBody::Init()
	{
		if (!rBody)
			MakeBody();
	}
	b2Body* PhysicBody::GetB2body()
	{
		if (!rBody)
			MakeBody();
		return rBody;
	}
	void PhysicBody::FixedUpdate()
	{
		lastRot = GetOwner()->rotation;
		lastPos = GetOwner()->position;
		GetOwner()->position = glm::vec2(rBody->GetPosition().x,rBody->GetPosition().y)*Game::GetInstance().BOX2D_TO_WORLD;
		GetOwner()->rotation = rBody->GetAngle();
		
	
	}
	void PhysicBody::MakeBody()
	{		rBody = Game::GetInstance().GetPhysicsService().RegisterBody(glm::vec2(owner->position.x, owner->position.y),kinematic,gravity,GetOwner()->rotation,angularDrag,drag, mass);
	}
	void PhysicBody::AddForce()
	{
		
	}

}