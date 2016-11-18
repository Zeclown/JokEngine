#ifndef COLLIDER_H
#define COLLIDER_H
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Component.h"
#include <boost\signals2.hpp>
#include <Box2D\Dynamics\b2Fixture.h>
#include "PhysicLayer.h"

class Collider: public Component
{
public:
	//Position relative to the center of the GameObject its attached to
	glm::vec2  offset;
	//Is it a solid collider or a trigger collider that sends events to the GameObject
	GLboolean isSolid;
	std::string physicLayer;
	Collider(GameObject* gameObject);
	GLfloat GetFriction();
	void SetFriction(GLfloat f);
	virtual ~Collider();
protected:
	GLfloat friction;
	b2Fixture *fixture; 
};


#endif // !COLLIDER_H

