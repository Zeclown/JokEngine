#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H
#include <gl\glew.h>
#include <glm\glm.hpp>
#include "Box2D\Dynamics\b2Body.h"
#include <vector>
#include <string>

namespace Jokengine
{
	class PhysicsService
	{	
		public:
			virtual glm::vec2 GetGravity() = 0;
			virtual void SetGravity(glm::vec2 gravity) = 0;
			virtual b2Body* RegisterBody(glm::vec2 position, GLboolean isKinematic, GLboolean isGravity, GLfloat rotation, GLfloat angularDrag, GLfloat drag, GLint mass)=0;
			virtual b2Fixture* RegisterFixtureBox(b2Body *body, glm::vec2 size = glm::vec2(1, 1), glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default")=0;
			virtual b2Fixture* RegisterFixtureCircle(b2Body *body, GLfloat radius = 1, glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default")=0;
			virtual b2Fixture* RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB, std::string layerName = "default")=0;
			virtual void SetMaskBits(std::string layerName, std::vector<std::string> otherLayers, GLboolean isColliding = true)=0;
			virtual void SetMaskBits(std::string layerName, std::string otherLayer, GLboolean isColliding = true) = 0;
			virtual void RegisterPhysicLayer(std::string layerName, uint16 maskBits = -1)=0;
			virtual uint16 GetCategoryBits(std::string layerName)=0;
			virtual uint16 GetMaskBits(std::vector<std::string> layerNames, GLboolean isColliding = true)=0;
			virtual uint16 GetMaskBits(std::string layerName, GLboolean isColliding=true)=0;

			virtual void FixedUpdate() = 0;


	};
}
#endif // !PHYSICS_SERVICE_H

