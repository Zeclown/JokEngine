#ifndef PHYSICBODY_H
#define PHYSICBODY_H
#include <glm\glm.hpp>
#include "Component.h"
#include <gl\glew.h>
#include "Box2D\Dynamics\b2Body.h"
namespace Jokengine
{
	class PhysicBody : public Component
	{
	public:
		PhysicBody(std::weak_ptr<GameObject> gameObject);
		glm::vec2 velocity;
		glm::vec2 angularVelocity;
		glm::vec2 velocityModifier;
		glm::vec2 lastPos;
		GLfloat lastRot;
		GLboolean freezeRotation;
		GLboolean kinematic;
		glm::vec2 centerOfMass;
		GLfloat mass;
		GLfloat drag;
		GLfloat angularDrag;
		GLboolean gravity;
		GLboolean interpolate;
		virtual void FixedUpdate();
		virtual glm::vec2 PhysicBody::ComputeForce();
	private:
		b2Body* rBody;
		void InitBody();

	};
}
#endif
