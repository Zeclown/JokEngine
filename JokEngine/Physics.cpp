#include "Physics.h"
#include "Box2D\Dynamics\b2Body.h"
#include "Game.h"
namespace Jokengine
{
	Physics::Physics()
		:physicWorld(new b2World(b2Vec2(0,0.981))),velocityIteration(7),positionIteration(3)
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
	b2Body* Physics::RegisterBody(b2BodyDef bodyDef, GLint mass)
	{
		b2Body *body = physicWorld->CreateBody(&bodyDef);

		b2PolygonShape baseFixture;
		baseFixture.SetAsBox(1,1);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;
		boxFixtureDef.filter.categoryBits = 0;
		boxFixtureDef.filter.maskBits = 0;
		body->CreateFixture(&boxFixtureDef);
		return body;

	}
	b2Fixture* Physics::RegisterFixtureBox(b2Body *body,glm::vec2 size, glm::vec2 offset)
	{
		b2PolygonShape baseFixture;
		baseFixture.SetAsBox(size.x, size.y);
		baseFixture.m_centroid.Set(offset.x, offset.y);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;	
		return body->CreateFixture(&boxFixtureDef);
	}
	b2Fixture* Physics::RegisterFixtureCircle(b2Body *body, GLfloat radius, glm::vec2 offset)
	{
		b2CircleShape baseFixture;
		baseFixture.m_radius=radius;
		baseFixture.m_p.Set(offset.x, offset.y);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;
		return body->CreateFixture(&boxFixtureDef);
	}
	void Physics::FixedUpdate()
	{
		physicWorld->Step(Game::GetInstance().fixedRefreshTime,velocityIteration,positionIteration);
	}
}