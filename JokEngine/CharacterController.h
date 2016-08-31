#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H
#include "Game.h"

class CharacterController :public ComponentCloneable<Component, CharacterController>
{
public:
	CharacterController(GameObject *gameObject);
	void Init();
	void Update();

};
#endif
