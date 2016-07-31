#ifndef PHYSICS_DEBUG_H
#define PHYSICS_DEBUG_H
#include "PhysicsService.h"
#include "Box2D\Box2D.h"
#include "Box2D\Dynamics\b2World.h"
#include "PhysicLayer.h"
#include "Physics.h"
#include <array>
namespace Jokengine
{
	class PhysicsDebug : public PhysicsService
	{
	public:
		PhysicsDebug();
		glm::vec2 GetGravity();
		void SetGravity(glm::vec2 gravity);
		b2Body* RegisterBody(glm::vec2 position, GLboolean isKinematic, GLboolean isGravity, GLfloat rotation, GLfloat angularDrag, GLfloat drag, GLint mass);
		b2Fixture* RegisterFixtureBox(b2Body *body, glm::vec2 size = glm::vec2(1, 1), glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default");
		b2Fixture* RegisterFixtureCircle(b2Body *body, GLfloat radius = 1, glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default");
		b2Fixture* RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB, std::string layerName = "default");
		void SetMaskBits(std::string layerName, std::vector<std::string> otherLayers, GLboolean isColliding = true);
		void SetMaskBits(std::string layerName, std::string otherLayer, GLboolean isColliding = true);
		void RegisterPhysicLayer(std::string layerName, uint16 maskBits = -1);
		uint16 GetMaskBits(std::vector<std::string> layerNames, GLboolean isColliding = true);
		uint16 GetMaskBits(std::string layerName, GLboolean isColliding = true);
		uint16 GetCategoryBits(std::string layerName);
		void FixedUpdate();
	private:
		PhysicsService *phys;

	};
}
#endif // !PHYSICS_H

