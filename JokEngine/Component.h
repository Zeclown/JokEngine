#ifndef COMPONENT_H
#define COMPONENT_H
#include "JObject.h"
#include <GL/glew.h>
#include <memory>
#include <iostream>


//basic declaration because of co dependency
class GameObject;

//abstract main component class
class Component : public JObject {
friend class GameObject;
public:
	virtual ~Component() {};
	Component(GameObject* gameObject);
	//is the component active
	GLboolean   enabled;
	//Get the current Owner of the component if it has one. 
	GameObject* GetOwner();
	virtual Component *clone() const = 0;
protected:
	virtual void Init() {};
	GameObject* owner;


};
template <typename Base, typename Derived>
class ComponentCloneable : public Base
{
public:
	using Base::Base;

	virtual Base *clone() const
	{
		return new Derived(static_cast<Derived const &>(*this));
	}
};


#endif