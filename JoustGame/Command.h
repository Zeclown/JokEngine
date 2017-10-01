#pragma once
#include "Knight.h"
class Command
{
public:
	virtual ~Command(){};
	virtual void Execute(Knight& go) = 0;
};