#pragma once
#include "Command.h"
class StopWalkingCommand :public Command
{
	virtual void Execute(Knight& knight);
};