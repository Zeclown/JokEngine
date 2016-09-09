#include "PhysicBody.h"
#include "Game.h"
#include "Box2D\Dynamics\b2Body.h"

PhysicBody::PhysicBody(GameObject* gameObject)
	:velocity(glm::vec2(0, 0)), freezeRotation(false), kinematic(false)
	, centerOfMass(glm::vec2(0, 0)), drag(0.0f), angularDrag(0.0f), gravity(true), interpolate(false), mass(1), angularVelocity(0), rBody(nullptr), ComponentCloneable(gameObject)
{
}
PhysicBody::PhysicBody(PhysicBody const & pb)
	: ComponentCloneable(pb), velocity(pb.velocity), freezeRotation(pb.freezeRotation), kinematic(pb.kinematic)
	, centerOfMass(pb.centerOfMass), drag(pb.drag), angularDrag(pb.angularDrag), gravity(pb.gravity), interpolate(pb.interpolate), mass(pb.mass), angularVelocity(pb.angularVelocity), rBody(nullptr)
{

}
void PhysicBody::Init()
{
	if (!rBody)
		MakeBody();
}
b2Body* PhysicBody::GetB2body()
{
	if (!rBody)
		MakeBody();
	return rBody;
}
void PhysicBody::FixedUpdate()
{
	lastRot = GetOwner()->rotation;
	lastPos = GetOwner()->position;
	GetOwner()->position = glm::vec2(rBody->GetPosition().x,rBody->GetPosition().y)*Game::GetInstance().BOX2D_TO_WORLD;
	GetOwner()->rotation = rBody->GetAngle();
		
	
}
void PhysicBody::MakeBody()
{	rBody = Game::GetInstance().GetPhysicsService().RegisterBody(this,glm::vec2(owner->position.x, owner->position.y),kinematic,gravity,GetOwner()->rotation,angularDrag,drag, mass,!freezeRotation);
}
void PhysicBody::AddForce(glm::vec2 force, E_FORCE_TYPE forceType)
{
	if(forceType==E_FORCE_TYPE::FORCE)
		rBody->ApplyForce(b2Vec2(force.x, force.y), rBody->GetWorldCenter(),true);
	else
		rBody->ApplyLinearImpulse(b2Vec2(force.x, force.y), rBody->GetWorldCenter(), true);
}

glm::vec2 PhysicBody::GetVelocity()
{
	return glm::vec2(rBody->GetLinearVelocity().x, rBody->GetLinearVelocity().y);
}

void PhysicBody::SetVelocity(glm::vec2 vlcy)
{
	velocity = vlcy;
	if (rBody)
		rBody->SetLinearVelocity(b2Vec2(vlcy.x, vlcy.y));
}

void PhysicBody::SetAngularVelocity(GLfloat vlcy)
{
	angularVelocity = vlcy;
	if (rBody)
		rBody->SetAngularVelocity(vlcy);
		
}

GLfloat PhysicBody::GetAngularVelocity()
{
	return angularVelocity;
}

GLfloat PhysicBody::GetMass()
{
	return mass;
}

void PhysicBody::SetMass(GLfloat m)
{
	mass = m;
	b2MassData mData;
	rBody->GetMassData(&mData);
	mData.mass = m;
	rBody->SetMassData(&mData);
}

GLfloat PhysicBody::GetDrag()
{
	return drag;
}

void PhysicBody::SetDrag(GLfloat d)
{
	drag = d;
	if (rBody)
		rBody->SetLinearDamping(d);
}

GLboolean PhysicBody::IsFreezeRotation()
{
	return freezeRotation;
}

void PhysicBody::SetFreezeRotation(GLboolean freeze)
{
	freezeRotation = freeze;
	if (rBody)
		rBody->SetFixedRotation(!freeze);
}

GLboolean PhysicBody::IsGravity()
{
	return gravity;
}

void PhysicBody::SetGravity(GLboolean g)
{
	gravity = g;
	if (rBody)
		rBody->SetGravityScale(g);
}

GLboolean PhysicBody::IsKinematic()
{
	return kinematic;
}

void PhysicBody::SetKinematic(GLboolean k)
{
	kinematic = k;
	if (rBody)
		if(k)
			rBody->SetType(b2BodyType::b2_kinematicBody);
		else
			rBody->SetType(b2BodyType::b2_dynamicBody);
}



