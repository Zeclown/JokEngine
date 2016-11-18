#include "EnemyKnight.h"
#include "Game.h"
#include "FadeOutHelper.h"
#include "CircleCollider.h"
EnemyKnight::EnemyKnight(GameObject * go)
	:ComponentCloneable(go), enemyID(0), egg(GameObject("Egg"))
{
	healthPoints = 1;
}
EnemyKnight::~EnemyKnight()
{
}
void EnemyKnight::Init()
{
	Knight::Init();
	egg.AddComponent<EnemyEgg>();
	egg.GetComponent<EnemyEgg>()->babyInside = owner;
	egg.GetComponent<EnemyEgg>()->enemyID = enemyID;
	egg.GetComponent<EnemyEgg>()->timeToRez = 3;
	CircleCollider* eggCollider = egg.AddComponent<CircleCollider>();
	eggCollider->physicLayer = "Egg";
	eggCollider->radius = 0.05f;
	SpriteDrawable *sd = egg.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Egg");
	ai = GetOwner()->GetActiveComponent<KnightAI>();
	egg.GetComponent<EnemyEgg>()->mngr = ai->mngr;
	signalConnections.push_back(owner->Update.connect(boost::bind(&EnemyKnight::Update, this)));
}

void EnemyKnight::Update()
{
	Knight::Update();
	std::vector<Command*> commands = ai->ProcessAI();
	for (int i = 0; i < commands.size(); i++)
	{
		commands.at(i)->Execute(*this);
	}
}

void EnemyKnight::Die()
{
	owner->SetActive(false);
	Game::GetInstance().Instantiate(egg)->position=owner->GetWorldPosition();
}
