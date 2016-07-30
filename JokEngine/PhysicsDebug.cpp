#include "PhysicsDebug.h"

namespace Jokengine
{
	PhysicsDebug::PhysicsDebug()
		:phys(new Physics())
	{

	}
	glm::vec2 PhysicsDebug::GetGravity()
	{
		return phys->GetGravity();
	}
	void PhysicsDebug::SetGravity(glm::vec2 gravity)
	{
		phys->SetGravity(gravity);
	}
	b2Body* PhysicsDebug::RegisterBody(glm::vec2 position, GLboolean isKinematic, GLboolean isGravity, GLfloat rotation, GLfloat angularDrag, GLfloat drag, GLint mass)
	{
		return phys->RegisterBody(position, isKinematic, isGravity, rotation, angularDrag, drag, mass);
	}
	b2Fixture* PhysicsDebug::RegisterFixtureBox(b2Body *body, glm::vec2 size, glm::vec2 offset, std::string layerName)
	{
		return(phys->RegisterFixtureBox(body, size, offset, layerName));
	}
	b2Fixture* PhysicsDebug::RegisterFixtureCircle(b2Body *body, GLfloat radius, glm::vec2 offset, std::string layerName)
	{
		return phys->RegisterFixtureCircle(body,  radius,  offset,  layerName);
	}
	b2Fixture* PhysicsDebug::RegisterFixtureEdge(b2Body *body, glm::vec2 pointA, glm::vec2 pointB, std::string layerName)
	{

		return phys->RegisterFixtureEdge(body, pointA, pointB, layerName);
	}
	void PhysicsDebug::SetMaskBits(std::string layerName, std::string otherLayer, GLboolean isColliding)
	{
		phys->SetMaskBits( layerName,  otherLayer,isColliding);
	}
	uint16 PhysicsDebug::GetCategoryBits(std::string layerName)
	{
		return phys->GetCategoryBits(layerName);
	}
	void PhysicsDebug::SetMaskBits(std::string layerName, std::vector<std::string> otherLayers, GLboolean isColliding)
	{
		phys->SetMaskBits( layerName, otherLayers,isColliding);
	}
	void PhysicsDebug::RegisterPhysicLayer(std::string layerName, uint16 maskBits)
	{
		phys->RegisterPhysicLayer(layerName, maskBits);
	}
	uint16 PhysicsDebug::GetMaskBits(std::string layerName, GLboolean isColliding)
	{
		return phys->GetMaskBits(layerName,isColliding);
	}
	uint16 PhysicsDebug::GetMaskBits(std::vector<std::string> layerNames, GLboolean isColliding)
	{
		return phys->GetMaskBits(layerNames,isColliding);
	}
	void PhysicsDebug::FixedUpdate()
	{
		phys->FixedUpdate();
	}
}