#ifndef RAYCAST_LISTENER_H
#define RAYCAST_LISTENER_H
class RaycastListener
{
	RaycastListener(RaycastHit *result=nullptr)
	RaycastHit* result;
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
};
#endif // !RaycastListener
