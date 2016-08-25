#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H
#include "Game.h"
using namespace Jokengine;
class CharacterController :public ComponentCloneable<Component, CharacterController>
{
public:
	CharacterController(Jokengine::GameObject *gameObject);
	void Init();
	void Update();

};
#endif
