#include "GameObject.h"
#include "Component.h"
#include "Game.h"
namespace Jokengine
{

	GameObject::GameObject()
		:position(glm::vec2(0,0)),size(glm::vec2(1,1)),rotation(0),name("GameObject"),tag(E_JTAG::Default),flagWorldPos(true)
	{

	}	
	GameObject::GameObject(std::string name)
		: position(glm::vec2(0, 0)), size(glm::vec2(1, 1)), rotation(0), name(name), tag(E_JTAG::Default), flagWorldPos(true)
	{

	}

	void GameObject::SetActive(GLboolean activeState)
	{
		active = activeState;
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