#pragma once
#include "Component.h"
#include "Command.h"
#include "InputReader.h"
class InputHandler :public ComponentCloneable<Component, InputHandler>
{
public:
	InputHandler(GameObject* go);
	~InputHandler();
	virtual void Init();
	std::vector<Command*>  HandleInput();
	int button_UP;
	int button_RIGHT;
	int button_LEFT;
private:

	Command* jumpCom;
	Command* moveLeftCom;
	Command* moveRightCom;
	InputReader* input;
};
