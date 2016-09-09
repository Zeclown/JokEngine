#pragma once
#include"Command.h"
class MoveLeftCommand :public Command
{
	virtual void Execute(Knight& knight);
};