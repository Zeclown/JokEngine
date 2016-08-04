#include "RaycastListener.h"
namespace Jokengine
{
	float32 RaycastListener::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		if(result)
		{
			result->collider=static_cast<Collider*>(fixture->getUserData());
			result->point=glm::vec2(point.x,point.y);
			result->normal=glm::vec2(normal.x,normal.y);
		}
		return fraction;
	}
}