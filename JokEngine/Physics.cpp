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
		bodyDef.position =b2Vec2( bodyDef.position.x * Game::GetInstance().WORLD_TO_BOX2D, bodyDef.position.y * Game::GetInstance().WORLD_TO_BOX2D);
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
		baseFixture.SetAsBox(size.x*Game::GetInstance().WORLD_TO_BOX2D, size.y*Game::GetInstance().WORLD_TO_BOX2D);
		baseFixture.m_centroid.Set(offset.x, offset.y);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;	
		return body->CreateFixture(&boxFixtureDef);
	}
	b2Fixture* Physics::RegisterFixtureCircle(b2Body *body, GLfloat radius, glm::vec2 offset)
	{
		b2CircleShape baseFixture;
		baseFixture.m_radius=radius*Game::GetInstance().WORLD_TO_BOX2D;
		baseFixture.m_p.Set(offset.x*Game::GetInstance().WORLD_TO_BOX2D, offset.y*Game::GetInstance().WORLD_TO_BOX2D);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;
		return body->CreateFixture(&boxFixtureDef);
	}
	b2Fixture* Physics::RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB)
	{

		b2EdgeShape es;
		es.Set(b2Vec2(pointA.x*Game::GetInstance().WORLD_TO_BOX2D, pointA.y*Game::GetInstance().WORLD_TO_BOX2D), b2Vec2(pointB.x*Game::GetInstance().WORLD_TO_BOX2D, pointB.y*Game::GetInstance().WORLD_TO_BOX2D));
		b2FixtureDef edgeFixtureDef;
		edgeFixtureDef.shape = &es;
		edgeFixtureDef.density = 1;
		return body->CreateFixture(&edgeFixtureDef);
	}
	void Physics::FixedUpdate()
	{
		physicWorld->Step(Game::GetInstance().fixedRefreshTime,velocityIteration,positionIteration);
	}
}