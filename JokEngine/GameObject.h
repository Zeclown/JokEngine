#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include "JObject.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <boost\optional.hpp>
namespace Jokengine
{
	class Component;
	enum E_JTAG
	{
		Default,Player,Floor,UI
	};
	//Base class representing all entities
	class GameObject : public JObject
	{
		friend class GameRoom;
	public:
		// Object state
		std::string name;
		E_JTAG tag;
		glm::vec2   position, size;
		GLfloat     rotation;

		
		// Constructor(s)
		GameObject();
		GameObject(std::string name = "GameObject");
		~GameObject() {};
		//Create a component and add it to the GameObject. Return a reference to the component
		template<typename T>
		std::weak_ptr<T>  AddComponent()
		{
			auto newComp = std::make_shared<T>(Game::GetInstance().FindByID(objectID));
			components.push_back(newComp);
			std::weak_ptr<T> ptr = newComp;
			return ptr;
		}
		////Add the specified component to the GameObject. Return a reference to the component
		//template<typename T>
		//std::weak_ptr<T> AddComponent(T &component)
		//{
		//	auto newComp = make_shared<T>(component&);
		//	newComp->Register(*this);
		//	components.push_back(newComp);
		//	std::weak_ptr<T> ptr = newComp;
		//	return ptr;
		//}
		//Remove the first occurence of a component of type <T> on the GameObject. Should use Component.Unregister() instead.
		template<typename T>
		std::shared_ptr<Component> RemoveComponent()
		{
			std::shared_ptr<Component> ptr;
			for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end();++it)
			{
				if (std::is_same<**it, T>::value)
				{					
					ptr.swap(*it);
					components.erase(it);
					break;
				}
			}
			return ptr;
		}
		//Remove the component specified from the GameObject.Should use Component.Unregister() instead.
		template<typename T>
		std::shared_ptr<Component> RemoveComponent(T &component)
		{
			std::shared_ptr<Component> ptr;
			for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it)
			{
				if(component == (*it).get())
				{
					ptr.swap(*it);
					components.erase(it);
					break;
				}
			}
			return ptr;
		}
		//Get the first occurence of a Component of type <T> on the GameObject. If none is found, returns uninitialised boost::optional
		template<typename T>
		std::weak_ptr<T> GetComponent()
		{
			for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it)
			{
				auto derived = std::dynamic_pointer_cast<T>(*it);
				if (derived != nullptr)
				{
					std::weak_ptr<T> compPointer(derived);
					return compPointer;
				}
			}
			return std::weak_ptr<T>();
		}
		//Get all occurences of a Component of type <T> on the GameObject. If none is found, returns uninitialised boost::optional
		template<typename T>
		std::vector<std::weak_ptr<T>> GetComponents()
		{
			std::vector<T&> toGet;
			for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it)
			{
				if (std::is_same<**it, T>::value)
					toGet.push_back(**it);
			}
			return toGet;
		}

		//Check if the game object is currently active
		GLboolean isActive();
		//Set the current active state of the GameObject
		void SetActive(GLboolean activeState);
		//Get the world position and update it if the dirty flag is on
		glm::vec2 getWorldPosition(GLboolean dirty=false);
		//dirty flag that check if world position needs to be recalculated
		GLboolean flagWorldPos;
	protected:
		//All the components owned by the object
		std::vector<std::shared_ptr<Component>> components;
		std::vector<std::shared_ptr<GameObject>> children;
		GLboolean    active;
		GLint objectID;
	};
}


#endif