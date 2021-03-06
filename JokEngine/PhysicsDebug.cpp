#include "PhysicsDebug.h"


PhysicsDebug::PhysicsDebug()
	:phys(new Physics())
{

}
glm::vec2 PhysicsDebug::GetGravity()
{
	std::cout << "Getting gravity X:" <<  phys->GetGravity().x << " Y:" << phys->GetGravity().y << std::endl;
	return phys->GetGravity();
}
void PhysicsDebug::SetGravity(glm::vec2 gravity)
{
	std::cout << "Setting gravity X:" << gravity.x << " Y:" << gravity.y << std::endl;
	phys->SetGravity(gravity);
}
b2Body* PhysicsDebug::RegisterBody(PhysicBody* pb,glm::vec2 position, GLboolean isKinematic, GLboolean isGravity, GLfloat rotation, GLfloat angularDrag, GLfloat drag, GLint mass, GLboolean isRotation)
{
	std::cout << "Registering body at position " << " X:" << position.x << " Y:" << position.y;
	return phys->RegisterBody(pb,position, isKinematic, isGravity, rotation, angularDrag, drag, mass, isRotation);
}
b2Fixture* PhysicsDebug::RegisterFixtureBox(b2Body *body,Collider* col, glm::vec2 size,GLboolean sensor, glm::vec2 offset, std::string layerName)
{
	std::cout << "Registering FixtureBox at position " << " X:" << body->GetPosition().x << " Y:" << body->GetPosition().x;
	return(phys->RegisterFixtureBox(body, col, size,sensor, offset, layerName));
}
b2Fixture* PhysicsDebug::RegisterFixtureCircle(b2Body *body, Collider* col, GLfloat radius,GLboolean sensor, glm::vec2 offset, std::string layerName)
{
	std::cout << "Registering FixtureCircle at position " << " X:" << body->GetPosition().x << " Y:" << body->GetPosition().x;
	return phys->RegisterFixtureCircle(body, col,  radius, sensor, offset,  layerName);
}
b2Fixture* PhysicsDebug::RegisterFixtureEdge(b2Body *body, Collider* col, glm::vec2 pointA, glm::vec2 pointB, std::string layerName)
{
	std::cout << "Registering FixtureEdge at position " << " X:" << body->GetPosition().x << " Y:" << body->GetPosition().x;
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
