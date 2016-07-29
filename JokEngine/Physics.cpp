#include "Physics.h"
#include "Box2D\Dynamics\b2Body.h"
#include "Game.h"
namespace Jokengine
{
	Physics::Physics()
		:physicWorld(new b2World(b2Vec2(0,0.981))),velocityIteration(7),positionIteration(3),layerCount(1)
	{
	    layers[0]=PhysicLayer();
		layers[0].name="default"
		for(int i=1;i<16;i++)
		{
			layers[i]=PhysicLayer(math.pow(2,i));
		}
	}
	glm::vec2 Physics::GetGravity()
	{
		return glm::vec2(physicWorld->GetGravity().x, physicWorld->GetGravity().y);
	}
	void Physics::SetGravity(glm::vec2 gravity)
	{
		physicWorld->SetGravity(b2Vec2(gravity.x, gravity.y));
	}
	b2Body* Physics::RegisterBody(glm::vec2 position,isKinematic,isGravity,rotation,angularDrag,drag,GLint mass)
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
	b2Fixture* Physics::RegisterFixtureBox(b2Body *body,glm::vec2 size, glm::vec2 offset,string layerName="default")
	{
		b2PolygonShape baseFixture;
		baseFixture.SetAsBox(size.x*Game::GetInstance().WORLD_TO_BOX2D, size.y*Game::GetInstance().WORLD_TO_BOX2D);
		baseFixture.m_centroid.Set(offset.x*Game::GetInstance().WORLD_TO_BOX2D, offset.y*Game::GetInstance().WORLD_TO_BOX2D);
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &baseFixture;
		boxFixtureDef.density = 1;	
		boxFixtureDef.filter.categoryBits=Game::GetPhysicServices().GetCategoryBits(layerName);
		boxFixtureDef.filter.maskBits=Game::GetPhysicServices().GetMaskBits(layerName);
		return body->CreateFixture(&boxFixtureDef);
	}
	b2Fixture* Physics::RegisterFixtureCircle(b2Body *body, GLfloat radius, glm::vec2 offset,string layerName="default")
	{
		b2CircleShape baseFixture;
		baseFixture.m_radius=radius*Game::GetInstance().WORLD_TO_BOX2D;
		baseFixture.m_p.Set(offset.x*Game::GetInstance().WORLD_TO_BOX2D, offset.y*Game::GetInstance().WORLD_TO_BOX2D);
		b2FixtureDef circleFixtureDef;
		circleFixtureDef.shape = &baseFixture;
		circleFixtureDef.density = 1;
		circleFixtureDef.filter.categoryBits=Game::GetPhysicServices().GetCategoryBits(layerName);
		circleFixtureDef.filter.maskBits=Game::GetPhysicServices().GetMaskBits(layerName);
		return body->CreateFixture(&circleFixtureDef);
	}
	b2Fixture* Physics::RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB,string layerName="default")
	{

		b2EdgeShape es;
		es.Set(b2Vec2(pointA.x*Game::GetInstance().WORLD_TO_BOX2D, pointA.y*Game::GetInstance().WORLD_TO_BOX2D), b2Vec2(pointB.x*Game::GetInstance().WORLD_TO_BOX2D, pointB.y*Game::GetInstance().WORLD_TO_BOX2D));
		b2FixtureDef edgeFixtureDef;
		edgeFixtureDef.shape = &es;
		edgeFixtureDef.density = 1;
		return body->CreateFixture(&edgeFixtureDef);
	}
	void Physics::SetMaskBits(string layerName,string otherLayer,GlBoolean isColliding)
	{
		vector<string> vec;
		vec.add(otherLayer);
		SetMaskBits(layerName,vec,isColliding);
		
	}
	void Physics::SetMaskBits(string layerName,vector<string> otherLayers,GlBoolean isColliding)
	{
		auto iter=std::find(layers.begin(), layers.end(), layers[i].name)
		if(iter!=layers.end())
		{
			mask|=GetMaskBits(otherLayers,isColliding)	
		}
		if(isColliding)
			iter->maskBits|=mask;
		else
			iter->maskBits&=mask;
	}
	void Physics::RegisterPhysicLayer(string layerName,uint16 maskBits=-1)
	{
		layers[layerCount].maskBits=maskBits;
		layers[layerCount++].name=layerName;
	}
	uint16 GetMaskBits(string layerName,GlBoolean isColliding)
	{
		uint16 mask=0;
		for(int i =0 ;i<layers.size();++i)
		{
			if(layers[i].name==layerName)
			{
				mask|=layers[i].maskBits;
			}
		}
		if(isColliding)
			return mask;
		return ~mask;
	}
	uint16 GetMaskBits(vector<string> layerNames,GlBoolean isColliding)
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
	void Physics::FixedUpdate()
	{
		physicWorld->Step(Game::GetInstance().fixedRefreshTime,velocityIteration,positionIteration);
	}
}