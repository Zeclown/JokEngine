#include "GameManager.h"
#include "BlinkingObject.h"
#include "TextUI.h"
#include "SpriteDrawable.h"
#include"FadeOutHelper.h"
#include "CircleCollider.h"
#include "AudioSource.h"
#include "InputHandler.h"
#include "PlayerKnight.h"
#include "BoxCollider.h"
#include "SpriteAnimator.h"
#include "EnemyManager.h"
#include "KnightAI.h"
#include "EnemyKnight.h"
#include "ScoreBoard.h"
#include "EnemyEgg.h"
void GameManager::Init()
{
	signalConnections.push_back(owner->Update.connect(boost::bind(&GameManager::Update, this)));


	game = &Game::GetInstance();
	//Make sure the game manager is not destroyed while the game still runs
	owner->dontDestroyOnClean = true;

	//Creating physics layers
	game->GetPhysicsService().RegisterPhysicLayer("Ground", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Player", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Lance", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Egg", 0);
	game->GetPhysicsService().RegisterPhysicLayer("EnemyLance", 0);
	game->GetPhysicsService().SetMaskBits("Egg", "Lance", true);
	game->GetPhysicsService().SetMaskBits("Egg", "Ground", true);
	game->GetPhysicsService().SetMaskBits("Lance", "Lance", true);
	game->GetPhysicsService().SetMaskBits("Lance", "EnemyLance", true);
	game->GetPhysicsService().SetMaskBits("EnemyLance", "Lance", true);
	game->GetPhysicsService().SetMaskBits("Player", "Ground", true);
	game->GetPhysicsService().SetMaskBits("Ground", "Player", true);
	//START MENU PROTOTYPES INIT
	GameObject titleScreen = GameObject("Title Screen");
	titleScreen.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSprite("TitleScreen");
	titleScreen.size = glm::vec2(62, 34);
	prefabs.insert(std::map< std::string, GameObject >::value_type("TitleScreen", titleScreen));

	GameObject musicBox = GameObject("MusicBox");
	AudioSource *as = musicBox.AddComponent<AudioSource>();
	as->RegisterSound(ResourceManager::GetAudioFile("MainTheme"), "MainTheme");
	as->looping = true;
	prefabs.insert(std::map< std::string, GameObject >::value_type("MusicBox", musicBox));

	GameObject startText = GameObject("StartUI");
	BlinkingObject* blinking=startText.AddComponent<BlinkingObject>();
	blinking->ui = true;
	blinking->secondsBeforeBlinks = 1;
	TextUI* txt=startText.AddComponent<TextUI>();
	txt->position = glm::vec2(0, 200);
	txt->justify = true;
	txt->scale = 1;
	txt->text = "Press Any Key";
	txt->color = glm::vec3(255 , 255, 255);
	prefabs.insert(std::map< std::string, GameObject >::value_type("StartUI", startText));

	GameObject cover = GameObject("CoverScreenWhite");
	SpriteDrawable* sd=cover.AddComponent<SpriteDrawable>();
	sd->drawOrder =200;
	sd->sprite = ResourceManager::GetSprite("Cover");
	cover.AddComponent<FadeOutHelper>();
	cover.size = glm::vec2(500, 500);
	cover.position = glm::vec2(0, 0);
	prefabs.insert(std::map< std::string, GameObject >::value_type("CoverScreenWhite", cover));


	
	
	//MAIN GAME PROTOTYPES INIT

	GameObject player = GameObject("Player");
	player.AddComponent<PhysicBody>()->SetDrag(0.5f);
	player.GetComponent<PhysicBody>()->SetFreezeRotation(true);
	player.AddComponent<BoxCollider>()->size = glm::vec2(0.01f, 0.5f);
	player.GetComponent<BoxCollider>()->physicLayer = "Player";
	BoxCollider* bc=player.AddComponent<BoxCollider>();
	bc->size= glm::vec2(0.6f, 0.5f);
	bc->physicLayer = "Lance";
	bc->isSolid = false;
	player.AddComponent<PlayerKnight>();
	player.AddComponent<InputHandler>();
	player.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[1];
	player.GetComponent<SpriteDrawable>()->drawOrder = 1;
	Animation anim = Animation(ResourceManager::GetSpritesheet("Knight1"),0,1);
	anim.wrapMode = E_ANIMATION_WRAPMODE::LOOP;
	player.AddComponent<SpriteAnimator>()->AddAnimation(anim,"Idle");
	Animation anim2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 2, 5,0.1f);
	Animation anim3 = Animation(ResourceManager::GetSpritesheet("Knight1"), 6, 6, 0.1f);
	Animation anim4 = Animation(ResourceManager::GetSpritesheet("Knight1"), 7, 7, 0.1f);
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim2, "Running");
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim3, "Flying");
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim4, "Jumping");
	player.size = glm::vec2(4, 4);
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player1", player));

	GameObject player2 = GameObject("Player2");
	player2.AddComponent<PhysicBody>()->SetDrag(0.5f);
	player2.GetComponent<PhysicBody>()->SetFreezeRotation(true);
	player2.AddComponent<BoxCollider>()->size = glm::vec2(0.01f, 0.5f);
	player2.GetComponent<BoxCollider>()->physicLayer = "Player";
	bc = player2.AddComponent<BoxCollider>();
	bc->size = glm::vec2(0.6f, 0.5f);
	bc->physicLayer = "Lance";
	bc->isSolid = false;
	player2.AddComponent<PlayerKnight>();
	player2.AddComponent<InputHandler>();
	player2.GetComponent<InputHandler>()->button_LEFT = GLFW_KEY_LEFT;
	player2.GetComponent<InputHandler>()->button_RIGHT = GLFW_KEY_RIGHT;
	player2.GetComponent<InputHandler>()->button_UP = GLFW_KEY_UP;
	player2.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight2").sprites[1];
	player2.GetComponent<SpriteDrawable>()->drawOrder = 1;
	anim = Animation(ResourceManager::GetSpritesheet("Knight2"), 0, 1);
	anim.wrapMode = E_ANIMATION_WRAPMODE::LOOP;
	player2.AddComponent<SpriteAnimator>()->AddAnimation(anim, "Idle");
	anim2 = Animation(ResourceManager::GetSpritesheet("Knight2"), 2, 5, 0.1f);
	anim3 = Animation(ResourceManager::GetSpritesheet("Knight2"), 6, 6, 0.1f);
	anim4 = Animation(ResourceManager::GetSpritesheet("Knight2"), 7, 7, 0.1f);
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim2, "Running");
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim3, "Flying");
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim4, "Jumping");
	player2.size = glm::vec2(4, 4);
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player2", player2));

	GameObject Platform = GameObject("Platform");
	Platform.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = Platform.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform");
	Platform.AddComponent<BoxCollider>()->size.y = 0.01f;
	Platform.GetComponent<BoxCollider>()->SetFriction(1);
	Platform.GetComponent<BoxCollider>()->offset.y = -3.3f;
	Platform.GetComponent<BoxCollider>()->physicLayer = "Ground";
	Platform.size = glm::vec2(35, 6);
	prefabs.insert(std::map< std::string, GameObject >::value_type("Platform", Platform));

	GameObject Platform2 = GameObject("Platform2");
	Platform2.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = Platform2.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform2");
	Platform2.AddComponent<BoxCollider>()->size.y = 0.01f;
	Platform2.GetComponent<BoxCollider>()->SetFriction(1);
	Platform2.GetComponent<BoxCollider>()->offset.y = -2.4f;
	Platform2.GetComponent<BoxCollider>()->physicLayer = "Ground";
	Platform2.size = glm::vec2(14, 4);
	prefabs.insert(std::map< std::string, GameObject >::value_type("Platform2", Platform2));

	GameObject Platform3 = GameObject("Platform3");
	Platform3.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = Platform3.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform3");
	Platform3.AddComponent<BoxCollider>()->size.y = 0.01f;
	Platform3.GetComponent<BoxCollider>()->SetFriction(1);
	Platform3.GetComponent<BoxCollider>()->offset.y = -2.4f;
	Platform3.size = glm::vec2(14, 4);
	Platform3.GetComponent<BoxCollider>()->physicLayer = "Ground";
	prefabs.insert(std::map< std::string, GameObject >::value_type("Platform3", Platform3));


	GameObject enemy1 = GameObject("OnionKnight");
	enemy1.AddComponent<KnightAI>()->type = E_AI_TYPE::NORMAL;
	enemy1.AddComponent<EnemyKnight>();
	enemy1.AddComponent<PhysicBody>()->SetDrag(0.5f);
	enemy1.GetComponent<PhysicBody>()->SetFreezeRotation(true);
	enemy1.AddComponent<BoxCollider>()->size = glm::vec2(0.01f, 0.5f);
	enemy1.GetComponent<BoxCollider>()->physicLayer = "Player";
	bc = enemy1.AddComponent<BoxCollider>();
	bc->size = glm::vec2(0.6f, 0.5f);
	bc->physicLayer = "EnemyLance";
	bc->isSolid = false;
	enemy1.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[1];
	enemy1.GetComponent<SpriteDrawable>()->drawOrder = 1;
	enemy1.AddComponent<SpriteAnimator>()->AddAnimation(anim, "Idle");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim2, "Running");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim3, "Flying");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim4, "Jumping");
	enemy1.size = glm::vec2(4, 4);
	prefabs.insert(std::map< std::string, GameObject >::value_type("OnionKnight", enemy1));


	GameObject enemyController = GameObject("Enemy Manager");
	EnemyManager* em=enemyController.AddComponent<EnemyManager>();
	em->enemyRatio = 2;
	em->spawnPoints = {glm::vec2(0,3),glm::vec2(0,5),glm::vec2(0,8),glm::vec2(0,11),glm::vec2(-0,3),glm::vec2(-0,5),glm::vec2(-0,8),glm::vec2(-0,11) };
	s_EnemyPrototype enemy1prot;
	enemy1prot.protoype = &prefabs.find("OnionKnight")->second;
	enemy1prot.rarity = 1;
	enemy1prot.startingWave = 0;
	em->enemiesPrototypes.push_back(enemy1prot);
	prefabs.insert(std::map< std::string, GameObject >::value_type("EnemyManager", enemyController));

	GameObject player1EmptyLife = GameObject("Player1EmptyLife");
	sd= player1EmptyLife.AddComponent<SpriteDrawable>();
	player1EmptyLife.position = glm::vec2(-20, 16);
	player1EmptyLife.size = glm::vec2(2, 2);
	sd->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[8];
	sd->drawOrder = 200;
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player1EmptyLife", player1EmptyLife));

	GameObject player1Life = GameObject("Player1Life");
	sd = player1Life.AddComponent<SpriteDrawable>();
	player1Life.size = glm::vec2(2, 2);
	sd->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[7];
	sd->drawOrder = 201;
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player1Life", player1Life));

	GameObject player2EmptyLife = GameObject("Player2EmptyLife");
	sd = player2EmptyLife.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSpritesheet("Knight2").sprites[8];
	player2EmptyLife.position = glm::vec2(11, 16);
	player2EmptyLife.size = glm::vec2(2, 2);
	sd->flipped = true;
	sd->drawOrder = 200;
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player2EmptyLife", player2EmptyLife));

	GameObject player2Life = GameObject("Player2Life");
	player2Life.size = glm::vec2(2, 2);
	sd = player2Life.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSpritesheet("Knight2").sprites[7];
	sd->drawOrder = 201;
	sd->flipped = true;
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player2Life", player2Life));

	GameObject scoreBoard = GameObject("ScoreBoard");
	ScoreBoard* sbComp=scoreBoard.AddComponent<ScoreBoard>();
	sbComp->lifePrototypes.push_back(&prefabs.find("Player1Life")->second);
	sbComp->lifePrototypes.push_back(&prefabs.find("Player2Life")->second);
	sbComp->emptyPrototypes.push_back(&prefabs.find("Player1EmptyLife")->second);
	sbComp->emptyPrototypes.push_back(&prefabs.find("Player2EmptyLife")->second);
	prefabs.insert(std::map< std::string, GameObject >::value_type("ScoreBoard", scoreBoard));
	prefabs.find("OnionKnight")->second.GetComponent<EnemyKnight>()->value = scoreBoard.GetComponent<ScoreBoard>()->ENEMY_VALUE;
	//Start the menu
	SetUpMenu();

}
void GameManager::Update()
{
	switch (state)
	{
	case E_GAME_STATE::GAME_MENU:
		if (InputReader::instance().isButtonDown(-1))
			SetUpActive();
		break;
	case E_GAME_STATE::GAME_PLAYING:
		if (InputReader::instance().isButtonDown(GLFW_KEY_ENTER))
			ActivatePlayer2();
		if (players.at(0)->healthPoints <= 0 && (players.at(1)->healthPoints <= 0 || !players.at(1)->GetOwner()->isActive()))//the game is over
		{
			SetUpScoreboard();
		}
		break;
	case E_GAME_STATE::GAME_SCOREBOARD:
		if (InputReader::instance().isButtonDown(-1))
			SetUpMenu();
		break;
	}
}
void GameManager::SetUpMenu()
{
	state = E_GAME_STATE::GAME_MENU;
	game->ClearRoom();
	game->Instantiate(prefabs.find("TitleScreen")->second);
	game->Instantiate(prefabs.find("MusicBox")->second)->GetComponent<AudioSource>()->PlaySound("MainTheme");
	game->Instantiate(prefabs.find("StartUI")->second);
}
void GameManager::SetUpActive()
{
	players.clear();
	state = E_GAME_STATE::GAME_PLAYING;
	game->ClearRoom();
	GameObject *player1=game->Instantiate(prefabs.find("Player1")->second);
	player1->position = glm::vec2(0, 0);
	players.push_back(player1->GetComponent<PlayerKnight>());

	GameObject *player2 = game->Instantiate(prefabs.find("Player2")->second);	
	player2->position = glm::vec2(0, 0);
	players.push_back(player2->GetComponent<PlayerKnight>());
	player2->GetComponent<PlayerKnight>()->playerNumber = 1;
	player2->SetActive(false);

	GameObject* em=game->Instantiate(prefabs.find("EnemyManager")->second);
	em->GetComponent<EnemyManager>()->players.push_back(player1->GetComponent<PlayerKnight>());
	em->GetComponent<EnemyManager>()->players.push_back(player2->GetComponent<PlayerKnight>());
	game->Instantiate(prefabs.find("CoverScreenWhite")->second);
	game->Instantiate(prefabs.find("Platform")->second)->position = glm::vec2(0, 18);
	game->Instantiate(prefabs.find("Platform2")->second)->position=glm::vec2(15,0);
	game->Instantiate(prefabs.find("Platform3")->second)->position = glm::vec2(-15, 0);
	//game->Instantiate(prefabs.find("Platform")->second)->position=glm::vec2(0,40);
	GameObject *outsideTop=game->Instantiate(prefabs.find("Platform")->second);
	outsideTop->position = glm::vec2(0, -73.0f);
	outsideTop->size = glm::vec2(outsideTop->size.x + 120, outsideTop->size.y);
	GameObject *sb = game->Instantiate(prefabs.find("ScoreBoard")->second);
	sb->GetComponent<ScoreBoard>()->players.push_back(player1->GetComponent<PlayerKnight>());
	sb->GetComponent<ScoreBoard>()->players.push_back(player2->GetComponent<PlayerKnight>());
}

void GameManager::SetUpScoreboard()
{
	game->ClearRoom();
	state = E_GAME_STATE::GAME_SCOREBOARD;
}

void GameManager::ActivatePlayer2()
{
	if (!players.at(1)->GetOwner()->isActive() && players.at(1)->healthPoints>0)
	{
		players.at(1)->GetOwner()->SetActive(true);
		players.at(1)->GetOwner()->position = glm::vec2(0, 0);
	}
}
