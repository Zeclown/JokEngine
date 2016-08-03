#include "Physics.h"
#include "Box2D\Dynamics\b2Body.h"
#include "Game.h"
#include <math.h>

namespace Jokengine
{
	Physics::Physics()
		:physicWorld(new b2World(b2Vec2(0, 0.981))), velocityIteration(7), positionIteration(3), layerCount(1), layers({}), contactListener(new ContactListener)
	{
		physicWorld->SetContactListener(contactListener);
	    layers[0]=PhysicLayer();
		layers[0].name = "default";
		for(int i=1;i<16;i++)
		{
			layers[i]=PhysicLayer(pow(2,i));
		}
	}
	Physics::~Physics()
	{
		delete contactListener;
		delete physicWorld;
	}
	glm::vec2 Physics::GetGravity()
	{
		return glm::vec2(physicWorld->GetGravity().x, physicWorld->GetGravity().y);
	}
	void Physics::SetGravity(glm::vec2 gravity)
	{
		physicWorld->SetGravity(b2Vec2(gravity.x, gravity.y));
	}
	b2Body* Physics::RegisterBody(PhysicBody *pb, glm::vec2 position,GLboolean isKinematic, GLboolean isGravity,GLfloat rotation, GLfloat angularDrag, GLfloat drag,GLint mass)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(position.x*Game::GetInstance().WORLD_TO_BOX2D,position.y*Game::GetInstance().WORLD_TO_BOX2D);
		if (isKinematic)
			bodyDef.type = b2_kinematicBody;
		else
			bodyDef.type = b2_dynamicBody;
		if (!isGravity)
		{
			bodyDef.gravityScale = 0;
		}
		else
		{
			bodyDef.gravityScale = 1;
		}
		bodyDef.angle = rotation;
		bodyDef.angularDamping = angularDrag;
		bodyDef.linearDamping = drag;
		b2Body *body = physicWorld->CreateBody(&bodyDef);
		body->SetUserData(pb);
		b2PolygonShape baseFixture;
		baseFixture.SetAsBox(0.1,0.1);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;
		boxFixtureDef.filter.categoryBits = 0;
		boxFixtureDef.filter.maskBits = 0;
		body->CreateFixture(&boxFixtureDef);
		return body;
	}
	b2Fixture* Physics::RegisterFixtureBox(b2Body *body,Collider *col,glm::vec2 size, glm::vec2 offset,std::string layerName)
	{
		b2PolygonShape baseFixture;
		baseFixture.SetAsBox(size.x/2*Game::GetInstance().WORLD_TO_BOX2D, size.y/2*Game::GetInstance().WORLD_TO_BOX2D);
		baseFixture.m_centroid.Set(offset.x*Game::GetInstance().WORLD_TO_BOX2D, offset.y*Game::GetInstance().WORLD_TO_BOX2D);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;	
		boxFixtureDef.filter.categoryBits=Game::GetInstance().GetPhysicsService().GetCategoryBits(layerName);
		boxFixtureDef.filter.maskBits=Game::GetInstance().GetPhysicsService().GetMaskBits(layerName);
		b2Fixture* fixture = body->CreateFixture(&boxFixtureDef);
		fixture->SetUserData(col);
		return fixture;
	}
	b2Fixture* Physics::RegisterFixtureCircle(b2Body *body, Collider *col, GLfloat radius, glm::vec2 offset,std::string layerName)
	{
		b2CircleShape baseFixture;
		baseFixture.m_radius=radius*Game::GetInstance().WORLD_TO_BOX2D;
		baseFixture.m_p.Set(offset.x*Game::GetInstance().WORLD_TO_BOX2D, offset.y*Game::GetInstance().WORLD_TO_BOX2D);
		b2FixtureDef circleFixtureDef;
		circleFixtureDef.shape = &baseFixture;
		circleFixtureDef.density = 1;
		circleFixtureDef.filter.categoryBits= Game::GetInstance().GetPhysicsService().GetCategoryBits(layerName);
		circleFixtureDef.filter.maskBits=Game::GetInstance().GetPhysicsService().GetMaskBits(layerName);
		b2Fixture* fixture = body->CreateFixture(&circleFixtureDef);
		fixture->SetUserData(col);
		return fixture;
	}
	b2Fixture* Physics::RegisterFixtureEdge(b2Body *body, Collider *col, glm::vec2 pointA, glm::vec2 pointB,std::string layerName)
	{

		b2EdgeShape es;
		es.Set(b2Vec2(pointA.x*Game::GetInstance().WORLD_TO_BOX2D, pointA.y*Game::GetInstance().WORLD_TO_BOX2D), b2Vec2(pointB.x*Game::GetInstance().WORLD_TO_BOX2D, pointB.y*Game::GetInstance().WORLD_TO_BOX2D));
		b2FixtureDef edgeFixtureDef;
		edgeFixtureDef.shape = &es;
		edgeFixtureDef.density = 1;
		b2Fixture* fixture = body->CreateFixture(&edgeFixtureDef);
		fixture->SetUserData(col);
		return fixture;
	}
	void Physics::SetMaskBits(std::string layerName,std::string otherLayer,GLboolean isColliding)
	{
		
		auto iter1 = std::find_if(layers.begin(), layers.end(), [&layerName](const PhysicLayer& obj) {return obj.name == layerName; });
		auto iter2 = std::find_if(layers.begin(), layers.end(), [&otherLayer](const PhysicLayer& obj) {return obj.name == otherLayer; });
		if (iter1 != layers.end() && iter2 != layers.end())
		{
			if (isColliding)
			{
				iter1->maskBits |= iter2->categoryBits;
				iter2->maskBits |= iter1->categoryBits;
			}
			else
			{
				iter1->maskBits &= ~(iter2->categoryBits);
				iter2->maskBits &= ~(iter1->categoryBits);
			}
		}
			

	}
	uint16 Physics::GetCategoryBits(std::string layerName)
	{
		auto iter = std::find_if(layers.begin(), layers.end(), [&layerName](const PhysicLayer& obj) {return obj.name == layerName; });
		return iter->categoryBits;
	}
	void Physics::SetMaskBits(std::string layerName,std::vector<std::string> otherLayers,GLboolean isColliding)
	{
		for (int i = 0; i < otherLayers.size(); i++)
		{
			SetMaskBits(layerName,otherLayers[i],isColliding);
		}
	}
	void Physics::RegisterPhysicLayer(std::string layerName,uint16 maskBits)
	{
		layers[layerCount].maskBits=maskBits;
		layers[layerCount++].name=layerName;
	}
	uint16 Physics::GetMaskBits(std::string layerName,GLboolean isColliding)
	{
		uint16 mask=0;
		for (PhysicLayer &layer : layers)
		{
			if(layer.name==layerName)
			{
				mask|= layer.maskBits;
			}
		}
		if(isColliding)
			return mask;
		return ~mask;
	}
	uint16 Physics::GetMaskBits(std::vector<std::string> layerNames,GLboolean isColliding)
	{
		uint16 mask=0;
		for(int i =0 ;i<layerNames.size();++i)
		{
				mask |=GetMaskBits(layerNames[i],isColliding);
		}
		if(isColliding)
			return mask;
		return ~mask;
	}
	GLboolean Physics::Raycast(glm::vec2 origin, glm::vec2 direction, GLfloat maxDistance, uint16 physicMask)
	{
		return true;
	}
	void Physics::Raycast(glm::vec2 origin, glm::vec2 direction, RaycastHit &output, GLfloat maxDistance, uint16 physicMask)
	{
		
	}
	void Physics::FixedUpdate()
	{
		physicWorld->Step(Game::GetInstance().fixedRefreshTime,velocityIteration,positionIteration);
	}
}