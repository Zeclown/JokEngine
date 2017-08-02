#pragma once
#include "Command.h"
class JumpCommand :public Command
{
	virtual void Execute(Knight& knight);
};