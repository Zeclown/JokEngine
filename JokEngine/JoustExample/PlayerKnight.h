#pragma once
#include "Knight.h"
#include "InputHandler.h"
class PlayerKnight :public ComponentCloneable<Knight, PlayerKnight>
{
public:
	PlayerKnight(GameObject* go);
	virtual void Init();
	virtual void Update();
	int playerNumber;
private:
	InputHandler* input;

};