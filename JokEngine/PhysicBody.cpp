#include "PhysicBody.h"
#include "Game.h"
#include "Box2D\Dynamics\b2Body.h"
namespace Jokengine
{
	PhysicBody::PhysicBody(GameObject* gameObject)
		:velocity(glm::vec2(0, 0)), velocityModifier(glm::vec2(1, 1)), freezeRotation(false), kinematic(false)
		, centerOfMass(glm::vec2(0, 0)), drag(0.5f), angularDrag(0.2f), gravity(true), interpolate(false), mass(1), angularVelocity(0,0), rBody(nullptr), ComponentCloneable(gameObject)
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
		{
			b2BodyDef bodyDef;			bodyDef.position.Set(owner->position.x*Game::GetInstance().WORLD_TO_BOX2D, owner->position.y*Game::GetInstance().WORLD_TO_BOX2D);			if (kinematic)				bodyDef.type = b2_kinematicBody;			else				bodyDef.type = b2_dynamicBody;			if (!gravity)			{				bodyDef.gravityScale = 0;			}			else			{				bodyDef.gravityScale = 1;			}			bodyDef.angle = glm::radians(GetOwner()->rotation);			bodyDef.angularDamping = angularDrag;			bodyDef.linearDamping = drag;			rBody = Game::GetInstance().GetPhysicsService().RegisterBody(bodyDef, mass);		}
	}
	b2Body* PhysicBody::GetB2body()
	{
		return rBody;
	}
	void PhysicBody::FixedUpdate()
	{
		lastRot = GetOwner()->rotation;
		lastPos = GetOwner()->position;
		GetOwner()->position = glm::vec2(rBody->GetPosition().x,rBody->GetPosition().y)*Game::GetInstance().BOX2D_TO_WORLD;
		GetOwner()->rotation = glm::degrees(rBody->GetAngle());
		
	
	}
	void PhysicBody::AddForce()
	{
		
	}

}