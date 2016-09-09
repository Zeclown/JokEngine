#include "PlayerKnight.h"
#include "GameObject.h"
#include "Game.h"
#include <cmath>
PlayerKnight::PlayerKnight(GameObject * go)
	:ComponentCloneable(go),playerNumber(0)
{

}
void PlayerKnight::Init()
{
	Knight::Init();
	input = GetOwner()->GetActiveComponent<InputHandler>();
	owner->Update.connect(boost::bind(&PlayerKnight::Update, this));
}

void PlayerKnight::Update()
{
	Knight::Update();
	std::vector<Command*> commands = input->HandleInput();
	for (int i = 0; i < commands.size(); i++)
	{
		commands.at(i)->Execute(*this);
	}
}


