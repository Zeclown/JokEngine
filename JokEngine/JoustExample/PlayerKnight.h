#pragma once
#include "Knight.h"
#include "InputHandler.h"
class PlayerKnight :public ComponentCloneable<Knight, PlayerKnight>
{
public:
	PlayerKnight(GameObject* go);
	virtual void Init();
	virtual void Update();
	virtual void Die();
	int playerNumber;
	int score;
private:
	InputHandler* input;

};