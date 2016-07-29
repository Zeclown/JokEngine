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
			virtual b2Body* RegisterBody(glm::vec2 position,isKinematic,isGravity,rotation,angularDrag,drag,GLint mass) = 0;
			virtual b2Fixture* RegisterFixtureBox(b2Body *body, glm::vec2 size=glm::vec2(1,1),glm::vec2 offset=glm::vec2(0,0)) = 0;
			virtual b2Fixture* RegisterFixtureCircle(b2Body *body, GLfloat radius = 1, glm::vec2 offset = glm::vec2(0, 0)) = 0;
			virtual b2Fixture* RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB)=0;
			virtual void RegisterPhysicLayer(string layerName,uint16 maskBits=0xFFFF)=0;
			virtual uint16 GetMaskBits(vector<string> layerNames)=0;
			virtual void FixedUpdate() = 0;


	};
}
#endif // !PHYSICS_SERVICE_H

