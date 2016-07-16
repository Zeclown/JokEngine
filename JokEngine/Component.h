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
		//is the component active
		GLboolean   enabled;
		//Register the Component to a new GameObject and Unregister it from the current owner if it has one
		void Register(GameObject& gameObject);
		//Unregister the component from its current owner
		void Unregister();
		//Get the current Owner of the component if it has one. Returns uninitialised boost::optional if it doesnt
		std::weak_ptr<GameObject> GetOwner();
		//Destructor
		virtual ~Component() = 0;
	protected:
		std::shared_ptr<GameObject> owner;


	};
}
#endif