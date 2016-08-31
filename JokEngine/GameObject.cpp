#include "GameObject.h"
#include "Component.h"
#include "Game.h"
#include "PhysicBody.h"


GameObject::GameObject()
	:GameObject("GameObject"+objectID)
{

}	
GameObject::GameObject(std::string name)
	: position(glm::vec2(0, 0)), size(glm::vec2(1, 1)), rotation(0), name(name), tag(E_JTAG::Default),parent(nullptr),active(true)
{
		
}
GameObject::GameObject(const GameObject &gameObject)
	: position(gameObject.position), size(gameObject.size), rotation(gameObject.rotation), name(gameObject.name), tag(gameObject.tag), parent(nullptr), active(true)
{

	for (size_t i = 0; i < gameObject.components.size(); i++)
	{

		AddComponent(*gameObject.components[i]);
	}
	for (size_t i = 0; i < gameObject.children.size(); i++)
	{
		GameObject* newChild=Game::GetInstance().Instantiate(*gameObject.children[i]);
		newChild->parent = this;
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
glm::vec2 GameObject::GetWorldPosition()
{
	GameObject* curParent;
	curParent = parent;
	glm::vec2 parentOffset;
	while (curParent)
	{
		parentOffset += curParent->position;
		curParent = curParent->parent;
	}
	return parentOffset+position;
}
glm::vec2 GameObject::GetWorldSize()
{
	GameObject* curParent;
	curParent = parent;
	glm::vec2 parentOffset;
	while (curParent)
	{
		parentOffset += curParent->size;
		curParent = curParent->parent;
	}
	return parentOffset + size;
}
GLfloat GameObject::GetWorldRotation()
{
	GameObject* curParent;
	curParent = parent;
	GLfloat parentOffset = 0.0f;
	while (curParent)
	{
		parentOffset += curParent->rotation;
		curParent = curParent->parent;
	}
	return parentOffset + rotation;
}
void GameObject::SetParent(GameObject * go)
{
	if (parent)//remove itself from the children of the old parent
	{
		for (int i = 0; i < parent->children.size(); i++)
		{
			if (parent->children[i]->objectID == objectID)
			{
				parent->children.erase(parent->children.begin()+i);
				break;
			}
		}
	}
	parent = go;
	if(parent)
		parent->children.push_back(this);
}
GameObject* GameObject::GetParent()
{
	return parent;
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


