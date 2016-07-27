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
		b2Body* RegisterBody(b2BodyDef bodyDef, GLint mass);
		b2Fixture* RegisterFixtureBox(b2Body *body, glm::vec2 size = glm::vec2(1, 1), glm::vec2 offset = glm::vec2(0, 0));
		b2Fixture* RegisterFixtureCircle(b2Body *body, GLfloat radius = 1, glm::vec2 offset = glm::vec2(0, 0));
		b2Fixture* RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB);
		void FixedUpdate();
	private:
		const int velocityIteration;
		const int positionIteration;
		b2World* physicWorld;



	};
}
#endif // !PHYSICS_H

