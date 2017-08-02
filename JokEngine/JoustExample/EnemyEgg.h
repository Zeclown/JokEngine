#pragma once
#include "Component.h"
#include "Collision.h"
#include "GameObject.h"
#include "EnemyManager.h"
class EnemyEgg :public ComponentCloneable<Component, EnemyEgg>
{
	using ComponentCloneable<Component, EnemyEgg>::ComponentCloneable;
public:
	~EnemyEgg();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(Collision col);
	virtual void Die(GameObject* Killer=nullptr);

	float timeToRez;
	GameObject* babyInside;
	EnemyManager* mngr;
	GameObject* playerOwner;
	int enemyID;
private:
	void SpawnEnemy();
	float rezTimer;
	GameObject scoreNotification;
};