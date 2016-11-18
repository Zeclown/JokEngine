#pragma once
#include "Knight.h"
#include "KnightAI.h"
#include "EnemyEgg.h"
class EnemyKnight :public ComponentCloneable<Knight, EnemyKnight>
{
public:
	EnemyKnight(GameObject* go);
	~EnemyKnight();
	virtual void Init();
	virtual void Update();
	virtual void Die();
	int enemyID;
	int value;
	GameObject egg;
private:
	KnightAI* ai;

};