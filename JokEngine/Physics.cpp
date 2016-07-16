#include "Physics.h"
#include "Box2D\Dynamics\b2Body.h"
#include "Game.h"
namespace Jokengine
{
	Physics::Physics()
		:physicWorld(new b2World(b2Vec2(0,0.981)))
	{

	}
	glm::vec2 Physics::GetGravity()
	{
		return glm::vec2(physicWorld->GetGravity().x, physicWorld->GetGravity().y);
	}
	void Physics::SetGravity(glm::vec2 gravity)
	{
		physicWorld->SetGravity(b2Vec2(gravity.x, gravity.y));
	}
	b2Body* Physics::RegisterBody(b2BodyDef bodyDef)
	{
		return physicWorld->CreateBody(&bodyDef);
	}
	void Physics::FixedUpdate()
	{
		physicWorld->Step(Game::GetInstance().fixedRefreshTime,velocityIteration,positionIteration);
	}
}