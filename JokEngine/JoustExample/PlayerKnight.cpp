#include "PlayerKnight.h"
#include "GameObject.h"
#include "Game.h"
#include "FadeOutHelper.h"
#include <cmath>
PlayerKnight::PlayerKnight(GameObject * go)
	:ComponentCloneable(go),playerNumber(0)
{
	healthPoints = 3;
	score = 0;
}
void PlayerKnight::Init()
{
	Knight::Init();
	input = GetOwner()->GetActiveComponent<InputHandler>();
	signalConnections.push_back(owner->Update.connect(boost::bind(&PlayerKnight::Update, this)));
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

void PlayerKnight::Die()
{
	owner->AddComponent<FadeOutHelper>()->timeToFadeInSeconds=0.3f;
}


