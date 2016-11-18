#pragma once
#include "Command.h"
class WingsDownCommand :public Command
{
	virtual void Execute(Knight& knight);
};