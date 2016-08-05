#ifndef RAYCAST_LISTENER_H
#define RAYCAST_LISTENER_H
namespace Jokengine
{
	class RaycastListener: public b2RayCastCallback
	{
		public:
			RaycastListener(RaycastHit *result=nullptr)
			RaycastHit* result;
			float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};
}
#endif // !RaycastListener
