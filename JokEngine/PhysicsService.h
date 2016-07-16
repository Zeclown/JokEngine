#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H
#include <gl\glew.h>
#include <glm\glm.hpp>
#include "Box2D\Dynamics\b2Body.h"
namespace Jokengine
{
	class PhysicsService
	{	
		public:
			virtual glm::vec2 GetGravity() = 0;
			virtual void SetGravity(glm::vec2 gravity) = 0;
			virtual b2Body* RegisterBody(b2BodyDef bodyDef) = 0;
			virtual void FixedUpdate() = 0;
	};
}
#endif // !PHYSICS_SERVICE_H

