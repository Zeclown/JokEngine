#include "RaycastListener.h"
namespace Jokengine
{
	RaycastListener::~RaycastListener()
	{
		if (resultOwner)
		{
			delete result;
		}
	}
	RaycastListener::RaycastListener(RaycastHit *result)
		:result(result),resultOwner(false)
	{
		if (!result)
		{
			result = new RaycastHit();
			resultOwner = true;
		}
	}
	float32 RaycastListener::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		if(result)
		{
			result->collider=static_cast<Collider*>(fixture->GetUserData());
			result->point=glm::vec2(point.x,point.y);
			result->normal=glm::vec2(normal.x,normal.y);
			return fraction;
		}
		return 0;
	}
}