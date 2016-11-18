#include "InputHandler.h"
#include <GLFW\glfw3.h>
#include "JumpCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "WingsDownCommand.h"
#include "StopWalkingCommand.h"
InputHandler::InputHandler(GameObject * go)
	:ComponentCloneable(go),button_UP(GLFW_KEY_W), button_RIGHT(GLFW_KEY_D), button_LEFT(GLFW_KEY_A)
{

}

InputHandler::~InputHandler()
{
	if(jumpCom)
		delete jumpCom;
	if(moveLeftCom)
		delete moveLeftCom;
	if(moveRightCom)
		delete moveRightCom;
}

void InputHandler::Init()
{
	input = &InputReader::instance();
	jumpCom = new JumpCommand();
	moveLeftCom = new MoveLeftCommand();
	moveRightCom = new MoveRightCommand();
	wingsDownCom = new WingsDownCommand();
	stopWalkingCom = new StopWalkingCommand();
}

std::vector<Command*> InputHandler::HandleInput()
{
	std::vector<Command*> commandQueue;
	if (input->isButtonUp(button_RIGHT) || input->isButtonUp(button_LEFT))
	{
		commandQueue.push_back(stopWalkingCom);
	}
	if (input->isButtonDown(button_UP))
	{
		commandQueue.push_back(jumpCom);
		commandQueue.push_back(wingsDownCom);
	}
	if (input->isButton(button_UP))
	{
		commandQueue.push_back(wingsDownCom);
	}
	if (input->isButton(button_LEFT))
	{
		commandQueue.push_back(moveLeftCom);
	}
	if (input->isButton(button_RIGHT))
	{
		commandQueue.push_back(moveRightCom);
	}

	return commandQueue;
}
