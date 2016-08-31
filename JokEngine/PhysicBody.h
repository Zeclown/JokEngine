#ifndef PHYSICBODY_H
#define PHYSICBODY_H
#include <glm\glm.hpp>
#include "Component.h"
#include <gl\glew.h>
#include "Box2D\Dynamics\b2Body.h"
#include <boost\signals2.hpp>

enum E_FORCE_TYPE { FORCE, IMPULSE };
//Component that marks the game object as subject to simulated physics. 
class PhysicBody : public ComponentCloneable<Component, PhysicBody>
{
		
public:
	boost::signals2::signal<void()> collisionSignal;
	boost::signals2::signal<void()> triggerSignal;
	PhysicBody(GameObject* gameObject);
	PhysicBody(PhysicBody const & pb);
	GLboolean interpolate;
	b2Body* GetB2body();
	virtual void FixedUpdate();
	virtual void AddForce(glm::vec2 force,E_FORCE_TYPE forceType= E_FORCE_TYPE::FORCE);

	glm::vec2 GetVelocity();
	void SetVelocity(glm::vec2 vlcy);
	void SetAngularVelocity(GLfloat vlcy);
	GLfloat GetAngularVelocity();
	GLfloat GetMass();
	void SetMass(GLfloat m);
	GLfloat GetDrag();
	void SetDrag(GLfloat d);
	GLboolean IsFreezeRotation();
	void SetFreezeRotation(GLboolean freeze);
	GLboolean IsGravity();
	void SetGravity(GLboolean g);
	GLboolean IsKinematic();
	void SetKinematic(GLboolean k);

	glm::vec2 lastPos;
	GLfloat lastRot;
protected:
	glm::vec2 velocity;
	GLfloat angularVelocity;
	GLboolean freezeRotation;
	GLboolean kinematic;
	glm::vec2 centerOfMass;

	GLfloat mass;
	GLfloat drag;
	GLfloat angularDrag;
	GLboolean gravity;
	virtual void Init();
	virtual void MakeBody();
	b2Body* rBody;

};

#endif
