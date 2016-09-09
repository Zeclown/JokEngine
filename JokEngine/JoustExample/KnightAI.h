#pragma once
#include "Knight.h"
#include "Command.h"
#include <vector>
#include "Component.h"
enum E_AI_TYPE {
	NORMAL
};
class KnightAI : public ComponentCloneable<Component,KnightAI>
{
	enum E_AI_STATE {
		MOVING
	};
	using ComponentCloneable<Component, KnightAI>::ComponentCloneable;
public:
	virtual void Init();
	std::vector<Command*>  ProcessAI();
	Knight* knight;
	E_AI_TYPE type;
private:
	E_AI_STATE state;
};