#include "GameObject.h"
#include "Component.h"
#include "Game.h"
#include "PhysicBody.h"
namespace Jokengine
{

	GameObject::GameObject()
		:GameObject("GameObject"+objectID)
	{

	}	
	GameObject::GameObject(std::string name)
		: position(glm::vec2(0, 0)), size(glm::vec2(1, 1)), rotation(0), name(name), tag(E_JTAG::Default), flagWorldPos(true)
	{
		
	}
	GameObject::GameObject(const GameObject &gameObject)
		: position(gameObject.position), size(gameObject.size), rotation(gameObject.rotation), name(gameObject.name), tag(gameObject.tag), flagWorldPos(true)
	{

		for (size_t i = 0; i < gameObject.components.size(); i++)
		{

			AddComponent(*gameObject.components[i]);
		}
	}
	GameObject::~GameObject()
	{
	for(int i =0;i<components.size();++i)
		delete components[i];

	}
	void GameObject::SetActive(GLboolean activeState)
	{
		active = activeState;
	}
	void GameObject::Init()
	{
		if (initList.size() > 0)
		{
			std::vector<Component*> curInitList = initList;
			for (auto& elem : curInitList)
			{
				elem->Init();
			}
			initList.clear();
		}
	}
	GLboolean GameObject::isActive()
	{
		return active;
	}
	glm::vec2 GameObject::getWorldPosition(GLboolean dirty)
	{
		return position;
	}

}