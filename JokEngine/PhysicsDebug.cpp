#include "PhysicsDebug.h"


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
b2Body* PhysicsDebug::RegisterBody(PhysicBody* pb,glm::vec2 position, GLboolean isKinematic, GLboolean isGravity, GLfloat rotation, GLfloat angularDrag, GLfloat drag, GLint mass, GLboolean isRotation)
{
	return phys->RegisterBody(pb,position, isKinematic, isGravity, rotation, angularDrag, drag, mass, isRotation);
}
b2Fixture* PhysicsDebug::RegisterFixtureBox(b2Body *body,Collider* col, glm::vec2 size,GLboolean sensor, glm::vec2 offset, std::string layerName)
{
	return(phys->RegisterFixtureBox(body, col, size,sensor, offset, layerName));
}
b2Fixture* PhysicsDebug::RegisterFixtureCircle(b2Body *body, Collider* col, GLfloat radius,GLboolean sensor, glm::vec2 offset, std::string layerName)
{
	return phys->RegisterFixtureCircle(body, col,  radius, sensor, offset,  layerName);
}
b2Fixture* PhysicsDebug::RegisterFixtureEdge(b2Body *body, Collider* col, glm::vec2 pointA, glm::vec2 pointB, std::string layerName)
{

	return phys->RegisterFixtureEdge(body, col,pointA, pointB, layerName);
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
