#include "Collider.h"
namespace Jokengine
{
	Collider::~Collider() {}
	Collider::Collider(GameObject* gameObject)
		:Component(gameObject),offset(glm::vec2(0,0)),isSolid(true),physicLayer("default")
	{

	}
}