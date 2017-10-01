#include "Prototype_Manager.h"
std::map< std::string, GameObject > PrototypeManager::prototypes;

void PrototypeManager::AddPrototype(std::string name,GameObject prototype)
{
	prototypes.insert(std::map< std::string, GameObject >::value_type(name, prototype));
}

GameObject & PrototypeManager::GetPrototype(std::string name)
{
	return prototypes[name];
}
