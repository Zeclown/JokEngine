#pragma once
#include "Component.h"
#include "GameObject.h"
#include <vector>
#include "PlayerKnight.h"
struct s_EnemyPrototype
{
	GameObject* protoype;
	int startingWave;
	int rarity;
};
class EnemyManager :public ComponentCloneable<Component, EnemyManager>
{
	 enum E_EManager_STATE
	 {
		 SPAWNING_WAVE, //In the process of spawning enemies
		 PAUSED, //Paused in the middle of the spawning process
		 WAITING //Spawning process completed, waiting for wave to be cleared
	 }; 
public:
	EnemyManager(GameObject *go);
	virtual void Init();
	virtual void Update();
	virtual void SignalDeath(int id,int playerID);
	int enemyRatio;
	int wave; //The current wave
	float timeBetweenSpawns;
	std::vector<PlayerKnight*> players;
	std::vector<glm::vec2> spawnPoints;
	std::vector<s_EnemyPrototype> enemiesPrototypes;
	std::vector<GameObject*> enemies;
	GameObject scoreText;
private:
	virtual void SpawnEnemy(std::vector<std::pair<GameObject*, float>> validPrototypes);
	//Returns a list of valid prototypes for the wave with spawn % probabilities for each
	virtual std::vector<std::pair<GameObject*,float>> GeneratePrototypeList();
	E_EManager_STATE state;
	float enemyLeftToSpawn;//Total of enemy to be spawned in the current wave
	float spawnTimer;
};