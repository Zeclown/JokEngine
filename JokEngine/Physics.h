#ifndef PHYSICS_H
#define PHYSICS_H
#include "PhysicsService.h"
#include "Box2D\Box2D.h"
#include "Box2D\Dynamics\b2World.h"
namespace Jokengine
{
	class Physics : public PhysicsService
	{
	public:
		Physics();
		glm::vec2 GetGravity();
		void SetGravity(glm::vec2 gravity);
		b2Body* RegisterBody(glm::vec2 position,isKinematic,isGravity,rotation,angularDrag,drag,GLint mass);
		b2Fixture* RegisterFixtureBox(b2Body *body, glm::vec2 size = glm::vec2(1, 1), glm::vec2 offset = glm::vec2(0, 0));
		b2Fixture* RegisterFixtureCircle(b2Body *body, GLfloat radius = 1, glm::vec2 offset = glm::vec2(0, 0));
		b2Fixture* RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB);
		void RegisterPhysicLayer(string layerName,uint16 maskBits=-1);
		uint16 GetMaskBits(vector<string> layerNames,GLboolean isColliding=true);
		void FixedUpdate();
	private:
		const int velocityIteration;
		const int positionIteration;
		int layerCount;
		PhysicLayer[16] layers;
		b2World* physicWorld;



	};
}
#endif // !PHYSICS_H

