#pragma once
#include "Component.h"
class ScoreText :public ComponentCloneable<Component, ScoreText>
{
	using ComponentCloneable<Component, ScoreText>::ComponentCloneable;
public:
	void Init();
	void Update();
	float speed;
	float duration;
};