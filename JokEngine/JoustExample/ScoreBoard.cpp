#include "ScoreBoard.h"
#include "GameObject.h"
#include "Game.h"
#include "TextUI.h"
#include "PlayerKnight.h"
void ScoreBoard::Update()
{
	for (int i = 0; i < 12; i++)
	{
		lives.at(i)->SetActive(false);
	}
	for (int i = 0; i < 2; i++)
	{
		for (int lifeIndex = 0; lifeIndex < players.at(i)->healthPoints; lifeIndex++)
		{
			lives.at(6*i+lifeIndex)->SetActive(true);
		}
	}
	textScores.at(0)->GetComponent<TextUI>()->text = std::to_string(players.at(0)->GetOwner()->GetComponent<PlayerKnight>()->score);
	textScores.at(1)->GetComponent<TextUI>()->text = std::to_string(players.at(1)->GetOwner()->GetComponent<PlayerKnight>()->score);
}
void ScoreBoard::Init()
{
	signalConnections.push_back(owner->Update.connect(boost::bind(&ScoreBoard::Update, this)));
	GameObject textProto = GameObject("Score");
	TextUI* tu=textProto.AddComponent<TextUI>();
	tu->text = "0";
	tu->justify = true;
	textScores.push_back(Game::GetInstance().Instantiate(textProto));
	textScores.at(0)->GetComponent<TextUI>()->color = glm::vec3(0,0,255);
	textScores.at(0)->GetComponent<TextUI>()->scale = 0.7f;
	textScores.at(0)->GetComponent<TextUI>()->position = glm::vec2(-315,340);
	textScores.push_back(Game::GetInstance().Instantiate(textProto));
	textScores.at(1)->GetComponent<TextUI>()->color = glm::vec3(255, 0, 0);
	textScores.at(1)->GetComponent<TextUI>()->scale = 0.7f;
	textScores.at(1)->GetComponent<TextUI>()->position = glm::vec2(315, 340);
	//Create the empty lives
	for (int i = 0; i < 2;i++)
		for (int j = 0; j < 6; j++)
		{
			GameObject* emptyLife=Game::GetInstance().Instantiate(*emptyPrototypes.at(i));
			emptyLife->position = glm::vec2(emptyLife->position.x+(j*2), emptyLife->position.y);
			GameObject* life= Game::GetInstance().Instantiate(*lifePrototypes.at(i));
			life->position = emptyLife->position;
			lives.push_back(life);
		}


}
