#ifndef PHYSICS_H
#define PHYSICS_H
#include "PhysicsService.h"
#include "Box2D\Box2D.h"
#include "Box2D\Dynamics\b2World.h"
#include "PhysicLayer.h"
#include <array>
#include "Collider.h"
#include "PhysicBody.h"
#include "ContactListener.h"

//Default Physic Service
class Physics : public PhysicsService
{
public:
	Physics();
	~Physics();
	glm::vec2 GetGravity();
	void SetGravity(glm::vec2 gravity);
	b2Body* RegisterBody(PhysicBody *pb,glm::vec2 position,GLboolean isKinematic,GLboolean isGravity,GLfloat rotation,GLfloat angularDrag,GLfloat drag,GLint mass,GLboolean isRotation);
	b2Fixture* RegisterFixtureBox(b2Body *body, Collider* col, glm::vec2 size = glm::vec2(1, 1),GLboolean sensor=false, glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default");
	b2Fixture* RegisterFixtureCircle(b2Body *body, Collider* col, GLfloat radius = 1,GLboolean sensor=false, glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default");
	b2Fixture* RegisterFixtureEdge(b2Body *body, Collider* col, glm::vec2 pointA, glm::vec2 pointB, std::string layerName = "default");
	void SetMaskBits(std::string layerName, std::vector<std::string> otherLayers, GLboolean isColliding=true);
	void SetMaskBits(std::string layerName, std::string otherLayer, GLboolean isColliding=true);
	void RegisterPhysicLayer(std::string layerName,uint16 maskBits=-1);
	uint16 GetMaskBits(std::vector<std::string> layerNames,GLboolean isColliding=true);
	uint16 GetMaskBits(std::string layerName, GLboolean isColliding=true);
	uint16 GetCategoryBits(std::string layerName);
	GLboolean Raycast(glm::vec2 origin, glm::vec2 direction, GLfloat maxDistance=1000, uint16 physicMask=-1);
	GLboolean Raycast(glm::vec2 origin, glm::vec2 direction, RaycastHit &output, GLfloat maxDistance=1000, uint16 physicMask=-1);
	std::vector<RaycastHit> RaycastAll(glm::vec2 origin, glm::vec2 direction, GLfloat maxDistance=1000, uint16 physicMask=-1);
	void FixedUpdate();
private:
	const int velocityIteration;
	const int positionIteration;
	int layerCount;
	std::array<PhysicLayer,16> layers;
	b2World* physicWorld;
	ContactListener* contactListener;



};

#endif // !PHYSICS_H

