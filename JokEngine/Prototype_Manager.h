#pragma once
#include "GameObject.h"
// A static Prototype_Manager class 
// It's a utility class that stores prefabs and can return them at an other time
// Glorified map for now but will have some added functionality
// Example:
//
//  PrototypeManager::AddPrototype("clown",MyGameObject)
//  GameObject* sprite=PrototypeManager::GetPrototype("clown");
class PrototypeManager
{
public:
	static void AddPrototype(std::string name, GameObject prototype);
	static GameObject& GetPrototype(std::string name);
private:
	static std::map< std::string, GameObject > prototypes;
};