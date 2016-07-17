#include "Component.h"
#include "GameObject.h"
namespace Jokengine
{
	Component::Component(std::weak_ptr<GameObject> gameObject)
		:owner(gameObject)
	{
	}
	GameObject* Component::GetOwner()
	{
		if (auto ptr = owner.lock())
		{
			return ptr.get();
		}
		else
		{
			return nullptr;
		}
	}
	Component::~Component() {}
}