#pragma once
#include"Command.h"
class MoveRightCommand :public Command
{
	virtual void Execute(Knight& knight);
};