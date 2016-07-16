#include "Component.h"
#include "GameObject.h"
namespace Jokengine
{
	void Component::Register(GameObject& gameObject)
	{
		Component::Unregister();	
		owner.reset(&gameObject);
	}
	void Component::Unregister()
	{
		if (owner)
		{
			owner->RemoveComponent(this);
			owner.reset();
		}
	}
	std::weak_ptr<GameObject> Component::GetOwner()
	{
		std::weak_ptr<GameObject> toReturn = owner;
		return toReturn;
	}
	Component::~Component() {}
}