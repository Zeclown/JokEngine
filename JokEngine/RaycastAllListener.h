#ifndef RAYCAST_ALL_LISTENER_H
#define RAYCAST_ALL_LISTENER_H
namespace Jokengine
{
	class RaycastAllListener : public b2RayCastCallback 
	{
		public:
			float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
			Vector<RaycastHit> hits;
	};
}
#endif