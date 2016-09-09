#include "JumpCommand.h"
#include "PhysicBody.h"
void JumpCommand::Execute(Knight& knight)
{
	knight.Jump();
}
