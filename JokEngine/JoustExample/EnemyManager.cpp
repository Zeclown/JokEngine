#include "EnemyManager.h"
#include "Game.h"
#include <time.h> 
#include "KnightAI.h"
#include "EnemyKnight.h"
#include "ScoreText.h"
#include "TextUI.h"
EnemyManager::EnemyManager(GameObject * go)
	:ComponentCloneable(go), enemyRatio(1), timeBetweenSpawns(1), spawnTimer(timeBetweenSpawns), wave(0),state(E_EManager_STATE::SPAWNING_WAVE), scoreText("ScoreText")
{
	
}

void EnemyManager::Init()
{
	signalConnections.push_back(owner->Update.connect(boost::bind(&EnemyManager::Update, this)));
	scoreText.AddComponent<ScoreText>();
	scoreText.AddComponent<TextUI>();
}

void EnemyManager::Update()
{
	switch (state)
	{
	case E_EManager_STATE::SPAWNING_WAVE:
		if (enemyLeftToSpawn > 0)
		{
			spawnTimer -= Game::GetInstance().GetTimeService().GetDeltaTime();
			if (spawnTimer <= 0)
			{
				spawnTimer = timeBetweenSpawns;
				SpawnEnemy(GeneratePrototypeList());
				enemyLeftToSpawn--;
			}
		}
		else
		{
			state = E_EManager_STATE::WAITING;
		}
		break;
	case E_EManager_STATE::PAUSED:
		break;
	case E_EManager_STATE::WAITING:
		if (enemies.size()==0)
		{
			state = E_EManager_STATE::SPAWNING_WAVE;
			wave++;
			enemyLeftToSpawn = (float)(wave+(int)(wave*0.5f))*enemyRatio;
		}
		break;
	}
}

void EnemyManager::SignalDeath(int id, int playerID)
{
	if (playerID != -1)
	{
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies.at(i)->GetComponent<EnemyKnight>()->enemyID == id)
			{
				players.at(playerID)->score += enemies.at(i)->GetComponent<EnemyKnight>()->value;
				enemies.erase(enemies.begin() + i);
				return;
			}
		}
	}
}



void EnemyManager::SpawnEnemy(std::vector<std::pair<GameObject*, float>> validPrototypes)
{
	float numberProtypePicked = (float)(rand() % 100);
	glm::vec2 spawnPicked = spawnPoints.at(rand() % spawnPoints.size());
	GameObject* prototypePicked=nullptr;
	for (size_t i = 0; i < validPrototypes.size(); i++)
	{
		numberProtypePicked -= validPrototypes.at(i).second;
		if (numberProtypePicked <= 0)
		{
			prototypePicked = validPrototypes.at(i).first;
			break;
		}
	}
	if (prototypePicked)
	{
		GameObject* newEnemy = Game::GetInstance().Instantiate(*prototypePicked);

		newEnemy->GetComponent<KnightAI>()->mngr = this;
		newEnemy->position = spawnPicked;
		newEnemy->GetComponent<EnemyKnight>()->enemyID = (int)enemyLeftToSpawn;
		enemies.push_back(newEnemy);
	}
}

std::vector<std::pair<GameObject*, float>> EnemyManager::GeneratePrototypeList()
{
	std::vector<s_EnemyPrototype> validPrototypes;
	std::vector<std::pair<GameObject*, float>> toReturn;
	float totalRarity=0;
	for (size_t i = 0; i < enemiesPrototypes.size(); i++)
	{
		if (enemiesPrototypes.at(i).startingWave <= wave)
		{
			totalRarity += enemiesPrototypes.at(i).rarity;
			validPrototypes.push_back(enemiesPrototypes.at(i));
		}
	}
	for (size_t i = 0; i < validPrototypes.size(); i++)
	{
		toReturn.push_back(std::pair<GameObject*, float>(validPrototypes.at(i).protoype, (validPrototypes.at(i).rarity / totalRarity) * 100));
	}
	return toReturn;
}


