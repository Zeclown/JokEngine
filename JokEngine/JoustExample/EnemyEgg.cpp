#include "EnemyEgg.h"
#include "Game.h"
#include "TextUI.h"
#include "ScoreText.h"
#include "EnemyKnight.h"
EnemyEgg::~EnemyEgg()
{

}
void EnemyEgg::Init()
{
	TextUI* txtUI=scoreNotification.AddComponent<TextUI>();
	txtUI->text = std::to_string(babyInside->GetComponent<EnemyKnight>()->value);
	txtUI->justify = true;
	txtUI->scale = 0.5f;
	txtUI->worldCoordinates = true;
	txtUI->color = glm::vec3(255, 255, 255);
	ScoreText* st=scoreNotification.AddComponent<ScoreText>();
	st->duration = 1;
	st->speed = 1;
	signalConnections.push_back(owner->Update.connect(boost::bind(&EnemyEgg::Update, this)));
	signalConnections.push_back(owner->OnCollisionEnter.connect(boost::bind(&EnemyEgg::OnCollisionEnter, this, _1)));
	rezTimer = timeToRez;
}

void EnemyEgg::Update()
{
	if (rezTimer <= 0)
	{
		SpawnEnemy();
	}
	rezTimer -= Game::GetInstance().GetTimeService().GetDeltaTime();
}
void EnemyEgg::OnCollisionEnter(Collision col)
{
	if (col.sensor)
	{
		Die(col.gameObject);
	}
}
void EnemyEgg::Die(GameObject * Killer)
{
	GameObject* go = Game::GetInstance().Instantiate(scoreNotification);
	go->GetComponent<TextUI>()->position = owner->position;
	int playerID;
	if (Killer == nullptr)
		playerID = playerOwner->GetComponent<PlayerKnight>()->playerNumber;
	else if (Killer->GetComponent<PlayerKnight>())
		playerID = Killer->GetComponent<PlayerKnight>()->playerNumber;
	else
		playerID = -1;
	mngr->SignalDeath(enemyID, playerID);
	if (playerID == 0)
	{
		go->GetComponent<TextUI>()->color = glm::vec3(0, 0, 255);
	}
	else if (playerID == 1)
	{
		go->GetComponent<TextUI>()->color = glm::vec3(255, 0, 0);
	}
	Game::GetInstance().Destroy(*babyInside);
	Game::GetInstance().Destroy(*owner);
}
void EnemyEgg::SpawnEnemy()
{
	babyInside->position = owner->position + glm::vec2(0, -0.7f);
	babyInside->SetActive(true);
	babyInside->GetComponent<Knight>()->Spawn();
	Game::GetInstance().Destroy(*owner);
}

