#ifndef RAYCAST_LISTENER_H
#define RAYCAST_LISTENER_H
#include "RaycastHit.h"

//Listener used by the default physics service
class RaycastListener: public b2RayCastCallback
{
	public:
		~RaycastListener();
		RaycastListener(RaycastHit *result = nullptr);
		RaycastHit *result;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
private:
	GLboolean resultOwner;
};

#endif // !RaycastListener
