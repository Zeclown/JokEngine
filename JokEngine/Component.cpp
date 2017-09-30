#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* gameObject)
	:owner(gameObject),enabled(true)
{
}
Component::~Component()
{
	for (size_t i = 0; i < signalConnections.size(); i++)
	{
		signalConnections.at(i).disconnect();
	}
	
}
GameObject* Component::GetOwner()
{
	return owner;
}
	

