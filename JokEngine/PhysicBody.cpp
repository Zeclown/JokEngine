#include "PhysicBody.h"
#include "Game.h"
#include "Box2D\Dynamics\b2Body.h"
namespace Jokengine
{
	PhysicBody::PhysicBody(std::weak_ptr<GameObject> gameObject)
		:velocity(glm::vec2(0, 0)), velocityModifier(glm::vec2(1, 1)), freezeRotation(false), kinematic(false)
		, centerOfMass(glm::vec2(0, 0)), drag(1), angularDrag(0.5f), gravity(true), interpolate(false), mass(1), angularVelocity(0,0), rBody(nullptr),Component(gameObject)
	{
		b2BodyDef bodyDef;		bodyDef.position.Set(GetOwner()->position.x, GetOwner()->position.y);		bodyDef.type = b2_dynamicBody;		bodyDef.angle = GetOwner()->rotation;		rBody = Game::GetPhysicsService().RegisterBody(bodyDef,mass);
	}
	void PhysicBody::InitBody()
	{


	}
	void PhysicBody::FixedUpdate()
	{
		lastRot = GetOwner()->rotation;
		lastPos = GetOwner()->position;
		GetOwner()->position = glm::vec2(rBody->GetPosition().x,rBody->GetPosition().y);
		GetOwner()->rotation = glm::degrees(rBody->GetAngle());
		//glm::vec2 force = ComputeForce();
		//glm::vec2 acceleration = force/mass;
		//velocity += acceleration  * Game::GetInstance().fixedRefreshTime;
		//owner->position += velocity * Game::GetInstance().fixedRefreshTime;

		
	}
	glm::vec2 PhysicBody::ComputeForce()
	{
		return Game::GetPhysicsService().GetGravity() * mass ;
	}
}