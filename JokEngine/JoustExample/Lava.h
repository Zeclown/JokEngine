#pragma once
#include "Component.h"
#include "Collision.h"
class Lava :public ComponentCloneable<Component, Lava>
{
public:
	Lava(GameObject* go);
	~Lava();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(Collision col);
};