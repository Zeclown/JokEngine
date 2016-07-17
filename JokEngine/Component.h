#ifndef COMPONENT_H
#define COMPONENT_H
#include "JObject.h"
#include <GL/glew.h>
#include <memory>
#include <iostream>

namespace Jokengine
{
	//basic declaration because of co dependency
	class GameObject;
	//abstract main component class
	class Component : public JObject {
	public:
		Component(std::weak_ptr<GameObject> gameObject);
		//is the component active
		GLboolean   enabled;
		//Get the current Owner of the component if it has one. 
		GameObject* GetOwner();
		//Destructor
		virtual ~Component() = 0;
	protected:
		std::weak_ptr<GameObject> owner;


	};
}
#endif