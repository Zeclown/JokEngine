#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H
#include "Box2D\Box2D.h"
#include "Collision.h"
#include <vector>
namespace Jokengine
{
	class ContactListener : public b2ContactListener
	{
	public:
		virtual void BeginContact(b2Contact* contact);
		virtual void EndContact(b2Contact* contact);
		void SendCollisionsCalls();
	private:
		virtual void PushCollision(b2Contact* contact,GLboolean enter);
		std::vector<Collision> collisionEnterList;
		std::vector<Collision> collisionExitList;
	};
}
#endif
