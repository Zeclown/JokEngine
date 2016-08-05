#include "RaycastAllListener.h"
namespace Jokengine
{
	float32 RaycastAllListener::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		RaycastHit hit;
		hit.collider=static_cast<Collider*>(fixture->getUserData());
		hit.point=glm::vec2(point.x,point.y);
		hit.normal=glm::vec2(normal.x,normal.y);
		hits.push_back(hit);
		return 1;
	}

}