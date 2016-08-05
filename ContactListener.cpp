#include "ContactListener.h"
#include "GameObject.h"
namespace Jokengine
{
	void ContactListener::PushCollision(b2Contact* contact,GLboolean enter)
	{
		b2Fixture *fixA = contact->GetFixtureA();
		b2Fixture *fixB = contact->GetFixtureB();
		Collider *colA = static_cast<Collider*>(fixA->GetUserData());
		Collider *colB = static_cast<Collider*>(fixB->GetUserData());
		PhysicBody *physA = static_cast<PhysicBody*>(fixA->GetBody()->GetUserData());
		PhysicBody *physB = static_cast<PhysicBody*>(fixB->GetBody()->GetUserData());
		GameObject *gameObjA = physA->GetOwner();
		GameObject *gameObjB = physB->GetOwner();
		std::vector<glm::vec2> contacts;
		int numContacts = contact->GetManifold()->pointCount;
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);
		for (int i = 0; i <= numContacts; ++i)
		{
			contacts.push_back(glm::vec2(worldManifold.points[i].x, worldManifold.points[i].y));
		}
		Collision col1 = Collision(colA, colB, physB, gameObjB, contacts,contact->IsSensor());
		Collision col2 = Collision(colB, colA, physA, gameObjA, contacts,contact->IsSensor());
		if (enter)
		{
			collisionEnterList.push_back(col1);
			collisionEnterList.push_back(col2);
		}
		else
		{
			collisionExitList.push_back(col1);
			collisionExitList.push_back(col2);
		}
	}
	void ContactListener::BeginContact(b2Contact* contact)
	{
		PushCollision(contact, true);
	}
	void ContactListener::EndContact(b2Contact* contact)
	{
		PushCollision(contact, false);
	}
	void ContactListener::SendCollisionsCalls()
	{
		for (int i = 0; i < collisionEnterList.size(); ++i)
		{
			collisionEnterList[i].colliderSelf->GetOwner()->OnCollisionEnter(collisionEnterList[i]);
		}
		for (int i = 0; i < collisionExitList.size(); ++i)
		{
			collisionExitList[i].colliderSelf->GetOwner()->OnCollisionExit(collisionExitList[i]);
		}
		collisionEnterList.clear();
		collisionExitList.clear();
	}
}
