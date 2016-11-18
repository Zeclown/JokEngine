#pragma once
#include "Knight.h"
#include "Command.h"
#include <vector>
#include "Component.h"
#include "EnemyManager.h"
enum E_AI_TYPE {
	NORMAL,PATROL,HUNTER
};
class KnightAI : public ComponentCloneable<Component,KnightAI>
{
	enum E_AI_STATE {
		MOVING,TARGETING
	};
	using ComponentCloneable<Component, KnightAI>::ComponentCloneable;
public:
	virtual void Init();
	std::vector<Command*>  ProcessAI();
	Knight* knight;
	E_AI_TYPE type;
	EnemyManager* mngr;
private:
	glm::vec2 target;
	E_AI_STATE state;
	float jumpTimer;
	Command* jumpCom;
	Command* moveLeftCom;
	Command* moveRightCom;
	Command* wingsDownCom;
	Command* stopWalkingCom;
};