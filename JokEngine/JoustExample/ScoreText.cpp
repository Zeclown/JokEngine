#include "ScoreText.h"
#include "Game.h"
#include "TextUI.h"
void ScoreText::Init()
{
	signalConnections.push_back(owner->Update.connect(boost::bind(&ScoreText::Update, this)));
	Game::GetInstance().Destroy(*owner, duration);

}

void ScoreText::Update()
{
	owner->GetComponent<TextUI>()->position.y -= speed*Game::GetInstance().GetTimeService().GetDeltaTime();
}
