#include "PhysicBody.h"
#include "Game.h"
#include "Box2D\Dynamics\b2Body.h"
namespace Jokengine
{
	PhysicBody::PhysicBody()
		:velocity(glm::vec2(0, 0)), velocityModifier(glm::vec2(1, 1)), freezeRotation(false), kinematic(false)
		, centerOfMass(glm::vec2(0, 0)), drag(1), angularDrag(0.5f), gravity(true), interpolate(false), mass(1), angularVelocity(0,0), rBody(nullptr)
	{

		//b2BodyDef* bodyDef = new b2BodyDef();		//bodyDef->position.Set(owner->position.x, owner->position.y);		//bodyDef.type = b2_dynamicBody;		//bodyDef.angle = owner->rotation;		rBody=Game::GetPhysicsService().RegisterBody(b2BodyDef());
	}
	void PhysicBody::FixedUpdate()
	{
		lastRot = owner->rotation;
		lastPos = owner->position;
		owner->position = glm::vec2(rBody->GetPosition().x,rBody->GetPosition().y);
		owner->rotation = rBody->GetAngle();
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