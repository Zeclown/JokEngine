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

	class Component;
	enum E_JTAG
	{
		Default,Player,Floor,UI
	};
	//Base class representing all entities
	//Can be assigned components to modify its behaviour
	//Needs to be Instantiated in gamespace by the Game instance
	// Example:
	//
	//  GameObject go = GameObject("Player");  //Create a base prototype
	//  go.AddComponent<CharacterController>(); //Add a custom component to it
	//  go.AddComponent<SpriteDrawable>().sprite= ResourceManager::GetSprite("Shark"); //Add a SpriteDrawable component to it and assign it a sprite
	//
	//  game.Instantiate(go); //Copy the prototype in gamespace

class GameObject : public JObject
{
	friend class GameRoom;
public:
	// Object state
	std::string name;
	E_JTAG tag;
	glm::vec2   position, size;
	GLfloat     rotation;
	GLboolean dontDestroyOnClean;
	// Constructor(s)
	GameObject();
	GameObject(std::string name);
	GameObject(const GameObject &gameObject);
	~GameObject();
	//Create a component and add it to the GameObject. Return a reference to the component
	template<typename T>
	T*  AddComponent()
	{
		auto newComp = new T(this);
		newComp->componentID = idCount;
		idCount++;
		components.push_back(newComp);
		initList.push_back(newComp);
		return newComp;
	}
	template<typename T>
	T*  AddComponent(T &component)
	{

		auto newComp = component.clone();
		newComp->owner = this;
		newComp->componentID = idCount;
		idCount++;
		components.push_back(newComp);
		initList.push_back(newComp);
		return newComp;
	}
	//Get the first occurence of a Component of type <T> on the GameObject. 
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
	//Get the first occurence of a Component of type <T> that is enabled on the GameObject. 
	template<typename T>
	T* GetActiveComponent()
	{
		for (auto const &comp : components)
		{
			auto derived = dynamic_cast<T*>(comp);
			if (derived != nullptr)
			{
				if(derived->enabled)
					return derived;
			}
		}
		return nullptr;
	}
	//Get all occurences of a Component of type <T> on the GameObject.
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
	//Set the parent of the GameObject in the hierarchy
	void SetParent(GameObject* go);
	GameObject* GetParent();
	int GetObjectID();
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
	GLint idCount;
	GLboolean    active;
	GLint objectID;
};



#endif