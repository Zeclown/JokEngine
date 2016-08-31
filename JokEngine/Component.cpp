#include "Component.h"
#include "GameObject.h"
namespace Jokengine
{
	Component::Component(GameObject* gameObject)
		:owner(gameObject),enabled(true)
	{
	}
	GameObject* Component::GetOwner()
	{
		return owner;
	}
	

}