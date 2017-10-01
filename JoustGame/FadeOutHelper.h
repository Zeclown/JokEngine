#pragma once
#include "Component.h"
#include "SpriteDrawable.h"
class FadeOutHelper : public ComponentCloneable<Component, FadeOutHelper>
{
	using ComponentCloneable<Component, FadeOutHelper>::ComponentCloneable;
public:
	void Init();
	void Update();
	float timeToFadeInSeconds;
private:
	float timer;
	SpriteDrawable *sp;

};