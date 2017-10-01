#pragma once
#include "Component.h"
#include "Knight.h"
class ScoreBoard :public ComponentCloneable<Component, ScoreBoard>
{
	using ComponentCloneable<Component, ScoreBoard>::ComponentCloneable;
public:
	virtual void Update();
	virtual void Init();
	std::vector<GameObject*> lifePrototypes;
	std::vector<GameObject*> emptyPrototypes;
	std::vector<Knight*> players;
	const int ENEMY_VALUE = 100;

private:
	std::vector<GameObject*> lives;
	std::vector<GameObject*> textScores;

};