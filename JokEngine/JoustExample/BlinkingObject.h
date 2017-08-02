#ifndef BLINKING_OBJECT_H
#define BLINKING_OBJECT_H
#include "Component.h"
class BlinkingObject : public ComponentCloneable<Component, BlinkingObject>
{
	using ComponentCloneable<Component, BlinkingObject>::ComponentCloneable;
public:
	void Init();
	void Update();
	float secondsBeforeBlinks;
	bool ui;//is it a ui component that needs to be deactivated

private:
	Component* displayComponent;
	bool blinking;
	float timer;

};

#endif // !BLINKING_OBJECT_H

