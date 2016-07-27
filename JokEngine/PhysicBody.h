#ifndef PHYSICBODY_H
#define PHYSICBODY_H
#include <glm\glm.hpp>
#include "Component.h"
#include <gl\glew.h>
#include "Box2D\Dynamics\b2Body.h"
#include <boost\signals2.hpp>
namespace Jokengine
{
	class PhysicBody : public ComponentCloneable<Component, PhysicBody>
	{
	public:
		boost::signals2::signal<void()> collisionSignal;
		boost::signals2::signal<void()> triggerSignal;
		PhysicBody(GameObject* gameObject);
		PhysicBody(PhysicBody const & pb);
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
		b2Body* GetB2body();
		virtual void FixedUpdate();
		virtual void AddForce();
	protected:
		virtual void Init();
		b2Body* rBody;

	};
}
#endif
