#pragma once
#include "Command.h"
class MoveCommand :public Command
{
	virtual void Execute(Knight& knight);
};