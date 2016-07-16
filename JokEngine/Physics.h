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
		b2Body* RegisterBody(b2BodyDef bodyDef);
		void FixedUpdate();
	private:
		const int velocityIteration=7;
		const int positionIteration=3;
		b2World* physicWorld;


	};
}
#endif // !PHYSICS_H

