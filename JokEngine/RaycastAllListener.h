#ifndef RAYCAST_ALL_LISTENER_H
#define RAYCAST_ALL_LISTENER_H
#include "Box2D\Box2D.h"
#include "RaycastHit.h"

//Listener used by the default physics service
class RaycastAllListener : public b2RayCastCallback 
{
	public:
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
		std::vector<RaycastHit> hits;
};

#endif