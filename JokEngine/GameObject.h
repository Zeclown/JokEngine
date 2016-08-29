#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include "JObject.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "Collision.h"
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
		GameObject(const GameObject &gameObject);
		~GameObject();
		//Create a component and add it to the GameObject. Return a reference to the component
		template<typename T>
		T*  AddComponent()
		{
			auto newComp = new T(this);
			components.push_back(newComp);
			initList.push_back(newComp);
			return newComp;
		}
		template<typename T>
		T*  AddComponent(T &component)
		{

			auto newComp = component.clone();
			newComp->owner = this;
			components.push_back(newComp);
			initList.push_back(newComp);
			return newComp;
		}
		//Get the first occurence of a Component of type <T> on the GameObject. If none is found, returns uninitialised boost::optional
		template<typename T>
		T* GetComponent()
		{
			for (auto const &comp : components)
			{
				auto derived = dynamic_cast<T*>(comp);
				if (derived != nullptr)
				{
					return derived;
				}
			}
			return nullptr;
		}
		//Get all occurences of a Component of type <T> on the GameObject. If none is found, returns uninitialised boost::optional
		template<typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> toGet;
			for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it)
			{
				if (std::is_same<**it, T>::value)
					toGet.push_back(**it);
			}
			return toGet;
		}
		glm::vec2 GetWorldPosition();
		glm::vec2 GetWorldSize();
		GLfloat GetWorldRotation();
		void SetParent(GameObject* go);
		GameObject* GetParent();
		void Init();
		//Check if the game object is currently active
		GLboolean isActive();
		//Set the current active state of the GameObject
		void SetActive(GLboolean activeState);
		//signals
		boost::signals2::signal<void()> Update;
		boost::signals2::signal<void()> FixedUpdate;
		boost::signals2::signal<void(Collision)> OnCollisionEnter;
		boost::signals2::signal<void(Collision)> OnCollisionExit;
	protected:
		//All the components owned by the object
		std::vector<Component*> components;
		std::vector<GameObject*> children;
		GameObject* parent;
		std::vector<Component*> initList;

		GLboolean    active;
		GLint objectID;
	};
}


#endif