#include "KnightAI.h"
#include "JumpCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "WingsDownCommand.h"
#include "StopWalkingCommand.h"
#include <cmath>
#include "Game.h"
#include <time.h>
void KnightAI::Init()
{
	jumpCom = new JumpCommand();
	moveLeftCom = new MoveLeftCommand();
	moveRightCom = new MoveRightCommand();
	wingsDownCom = new WingsDownCommand();
	stopWalkingCom = new StopWalkingCommand();
	state = E_AI_STATE::TARGETING;
	jumpTimer = 0;

	srand(time(NULL));
}

std::vector<Command*> KnightAI::ProcessAI()
{
	std::vector<Command*> commands;
	switch (type)
	{
	case E_AI_TYPE::NORMAL:	
		if (abs(target.x - owner->GetWorldPosition().x + target.y - owner->GetWorldPosition().y) < 1)
		{
			state = E_AI_STATE::TARGETING;
		}
		if (state == E_AI_STATE::TARGETING)
		{
			target = glm::vec2(rand() % 66 - 33, (rand() - 13) % 13);
			state = E_AI_STATE::MOVING;
		}
		//We have a target
		//Now we handle the x position
		if(abs(target.x-owner->GetWorldPosition().x)>30) //need to go the other way and use the out of bounds teleportation
		{
			if (target.x - owner->GetWorldPosition().x > 0)
			{
				commands.push_back(moveLeftCom);
			}
			else
			{
				commands.push_back(moveRightCom);
			}
		}
		else
		{
			if (target.x - owner->GetWorldPosition().x > 2)
			{
				commands.push_back(moveRightCom);
			}
			else if(target.x - owner->GetWorldPosition().x < -2)
			{
				commands.push_back(moveLeftCom);
			}
		}
		//Y position
		if (target.y - owner->GetWorldPosition().y < 0 && jumpTimer<=0)
		{
			commands.push_back(jumpCom);
			jumpTimer =  0.2f;
		}
		if (jumpTimer > 0.1f)
		{
			commands.push_back(wingsDownCom);
		}
		jumpTimer -= Game::GetInstance().GetTimeService().GetDeltaTime();

	}


	return commands;
}
