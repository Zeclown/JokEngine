#ifndef COLLIDER_H
#define COLLIDER_H
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <boost\signals2.hpp>
class Collider
{
public:
	boost::signals2::signal<void()> collisionSignal;
	boost::signals2::signal<void()> triggerSignal;
	//Position relative to the center of the GameObject its attached to
	glm::vec2   Offset;
	//Is it a solid collider or a trigger collider that sends events to the GameObject
	GLboolean IsSolid;
	virtual ~Collider() = 0;
};
Collider::~Collider() {}
#endif // !COLLIDER_H

