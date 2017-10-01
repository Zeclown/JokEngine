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
#include "Lava.h"
#include "SpriteAnimator.h"
#include "EnemyManager.h"
#include "KnightAI.h"
#include "EnemyKnight.h"
#include "ScoreBoard.h"
#include "EnemyEgg.h"
#include "Prototype_Manager.h"
void GameManager::Init()
{
	signalConnections.push_back(owner->Update.connect(boost::bind(&GameManager::Update, this)));


	game = &Game::GetInstance();
	//Make sure the game manager is not destroyed while the game still runs
	owner->dontDestroyOnClean = true;

	//Creating physics layers
	game->GetPhysicsService().RegisterPhysicLayer("Ground", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Lava", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Player", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Lance", 0);
	game->GetPhysicsService().RegisterPhysicLayer("Egg", 0);
	game->GetPhysicsService().RegisterPhysicLayer("EnemyLance", 0);
	game->GetPhysicsService().SetMaskBits("Egg", "Lava", true);
	game->GetPhysicsService().SetMaskBits("Player", "Lava", true);
	game->GetPhysicsService().SetMaskBits("EnemyLance", "Lava", true);
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
	PrototypeManager::AddPrototype("TitleScreen", titleScreen);

	GameObject musicBox = GameObject("MusicBox");
	AudioSource *as = musicBox.AddComponent<AudioSource>();
	as->RegisterSound(ResourceManager::GetAudioFile("MainTheme"), "MainTheme");
	as->looping = true;
	PrototypeManager::AddPrototype("MusicBox", musicBox);

	GameObject nameBox = GameObject("InputScore");
	InputBox* inputComp = nameBox.AddComponent<InputBox>();
	inputComp->maxCharacters = 3;
	inputComp->position= glm::vec2(0, 0);
	inputComp->justify = true;
	inputComp->scale = 1;
	inputComp->isTruncating = true;
	inputComp->color = glm::vec3(255, 255, 255);
	PrototypeManager::AddPrototype("InputBoxLB", nameBox);

	GameObject highScoreCongrats = GameObject("CongratsUI");
	TextUI* txtCongrats = highScoreCongrats.AddComponent<TextUI>();
	txtCongrats->position = glm::vec2(0, 200);
	txtCongrats->justify = true;
	txtCongrats->scale = 1;
	txtCongrats->text = "New Highscore! Congrats ";
	txtCongrats->color = glm::vec3(0, 255, 255);
	PrototypeManager::AddPrototype("CongratsUI", highScoreCongrats);

	GameObject highScore = GameObject("LeaderboardEntry");
	TextUI* txtScoreEntry = highScore.AddComponent<TextUI>();
	txtScoreEntry->position = glm::vec2(0, -220);
	txtScoreEntry->justify = true;
	txtScoreEntry->scale = 1;
	txtScoreEntry->color = glm::vec3(255, 255, 255);
	PrototypeManager::AddPrototype("LeaderboardEntry", highScore);

	GameObject LeaderBoardHeader = GameObject("LeaderboardHeader");
	TextUI* txtLBHeader = LeaderBoardHeader.AddComponent<TextUI>();
	txtLBHeader->position = glm::vec2(0, -220);
	txtLBHeader->justify = true;
	txtLBHeader->scale = 1;
	txtLBHeader->text = "Rank\tScore\tName";
	txtLBHeader->color = glm::vec3(255, 255, 255);
	PrototypeManager::AddPrototype("LeaderboardHeader", LeaderBoardHeader);

	GameObject MainLeaderBoard = GameObject("Leaderboard");
	MainLeaderBoard.AddComponent<LeaderBoard>();
	PrototypeManager::AddPrototype("Leaderboard", MainLeaderBoard);

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
	PrototypeManager::AddPrototype("StartUI", startText);

	GameObject cover = GameObject("CoverScreenWhite");
	SpriteDrawable* sd=cover.AddComponent<SpriteDrawable>();
	sd->drawOrder =200;
	sd->sprite = ResourceManager::GetSprite("Cover");
	cover.AddComponent<FadeOutHelper>();
	cover.size = glm::vec2(500, 500);
	cover.position = glm::vec2(0, 0);
	PrototypeManager::AddPrototype("CoverScreenWhite", cover);


	
	
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
	player.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight3").sprites[9];
	player.GetComponent<SpriteDrawable>()->drawOrder = 1;
	Animation anim1Player1 = Animation(ResourceManager::GetSpritesheet("Knight3"),0,1);
	anim1Player1.wrapMode = E_ANIMATION_WRAPMODE::LOOP;
	Animation anim2Player1 = Animation(ResourceManager::GetSpritesheet("Knight3"), 2, 5,0.1f);
	Animation anim3Player1 = Animation(ResourceManager::GetSpritesheet("Knight3"), 6, 6, 0.1f);
	Animation anim4Player1 = Animation(ResourceManager::GetSpritesheet("Knight3"), 7, 7, 0.1f);
	Animation anim5Player1 = Animation(ResourceManager::GetSpritesheet("Knight3"), 9, 14, 0.1f);
	anim5Player1.wrapMode = E_ANIMATION_WRAPMODE::CLAMP;
	player.AddComponent<SpriteAnimator>()->AddAnimation(anim1Player1, "Idle");
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim2Player1, "Running");
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim3Player1, "Flying");
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim4Player1, "Jumping");
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim5Player1, "Spawning");
	player.size = glm::vec2(4, 4);
	PrototypeManager::AddPrototype("Player1", player);

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
	player2.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[9];
	player2.GetComponent<SpriteDrawable>()->drawOrder = 1;
	Animation animPlayer2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 0, 1);
	animPlayer2.wrapMode = E_ANIMATION_WRAPMODE::LOOP;
	player2.AddComponent<SpriteAnimator>()->AddAnimation(animPlayer2, "Idle");
	Animation anim2Player2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 2, 5, 0.1f);
	Animation anim3Player2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 6, 6, 0.1f);
	Animation anim4Player2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 7, 7, 0.1f);
	Animation anim5Player2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 9, 14, 0.1f);
	anim5Player2.wrapMode = E_ANIMATION_WRAPMODE::CLAMP;
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim2Player2, "Running");
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim3Player2, "Flying");
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim4Player2, "Jumping");
	player2.GetComponent<SpriteAnimator>()->AddAnimation(anim5Player2, "Spawning");
	player2.size = glm::vec2(4, 4);
	PrototypeManager::AddPrototype("Player2", player2);

	GameObject Platform = GameObject("Platform");
	Platform.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = Platform.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform");
	Platform.AddComponent<BoxCollider>()->size.y = 0.01f;
	Platform.GetComponent<BoxCollider>()->SetFriction(1);
	Platform.GetComponent<BoxCollider>()->offset.y = -3.3f;
	Platform.GetComponent<BoxCollider>()->physicLayer = "Ground";
	Platform.size = glm::vec2(35, 6);
	PrototypeManager::AddPrototype("Platform", Platform);

	GameObject Platform2 = GameObject("Platform2");
	Platform2.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = Platform2.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform2");
	Platform2.AddComponent<BoxCollider>()->size.y = 0.01f;
	Platform2.GetComponent<BoxCollider>()->SetFriction(1);
	Platform2.GetComponent<BoxCollider>()->offset.y = -2.4f;
	Platform2.GetComponent<BoxCollider>()->physicLayer = "Ground";
	Platform2.size = glm::vec2(14, 4);
	PrototypeManager::AddPrototype("Platform2", Platform2);

	GameObject Platform3 = GameObject("Platform3");
	Platform3.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = Platform3.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform3");
	Platform3.AddComponent<BoxCollider>()->size.y = 0.01f;
	Platform3.GetComponent<BoxCollider>()->SetFriction(1);
	Platform3.GetComponent<BoxCollider>()->offset.y = -2.4f;
	Platform3.size = glm::vec2(14, 4);
	Platform3.GetComponent<BoxCollider>()->physicLayer = "Ground";
	PrototypeManager::AddPrototype("Platform3", Platform3);

	GameObject lava = GameObject("Lava");
	lava.AddComponent<Lava>();
	lava.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = lava.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Lava");
	lava.AddComponent<BoxCollider>();
	lava.GetComponent<BoxCollider>()->isSolid = false;
	lava.GetComponent<BoxCollider>()->physicLayer = "Lava";
	lava.size = glm::vec2(100, 5);
	PrototypeManager::AddPrototype("Lava", lava);

	GameObject enemy1 = GameObject("OnionKnight");
	Animation animEnemy = Animation(ResourceManager::GetSpritesheet("Knight2"), 0, 1);
	animEnemy.wrapMode = E_ANIMATION_WRAPMODE::LOOP;
	player2.AddComponent<SpriteAnimator>()->AddAnimation(animEnemy, "Idle");
	Animation anim2Enemy = Animation(ResourceManager::GetSpritesheet("Knight2"), 2, 5, 0.1f);
	Animation anim3Enemy = Animation(ResourceManager::GetSpritesheet("Knight2"), 6, 6, 0.1f);
	Animation anim4Enemy = Animation(ResourceManager::GetSpritesheet("Knight2"), 7, 7, 0.1f);
	Animation anim5Enemy = Animation(ResourceManager::GetSpritesheet("Knight2"), 9, 15, 0.1f);
	anim5Enemy.wrapMode = E_ANIMATION_WRAPMODE::CLAMP;
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
	enemy1.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight2").sprites[9];
	enemy1.GetComponent<SpriteDrawable>()->drawOrder = 1;
	enemy1.AddComponent<SpriteAnimator>()->AddAnimation(animEnemy, "Idle");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim2Enemy, "Running");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim3Enemy, "Flying");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim4Enemy, "Jumping");
	enemy1.GetComponent<SpriteAnimator>()->AddAnimation(anim5Enemy, "Spawning");
	enemy1.size = glm::vec2(4, 4);
	PrototypeManager::AddPrototype("OnionKnight", enemy1);


	GameObject enemyController = GameObject("Enemy Manager");
	EnemyManager* em=enemyController.AddComponent<EnemyManager>();
	em->enemyRatio = 2;
	em->spawnPoints = { glm::vec2(-13, 13.5),glm::vec2(13, 13.5),glm::vec2(15, -3.9f), glm::vec2(-15, -3.9f) };
	s_EnemyPrototype enemy1prot;
	enemy1prot.protoype = &PrototypeManager::GetPrototype("OnionKnight");
	enemy1prot.rarity = 1;
	enemy1prot.startingWave = 0;
	em->enemiesPrototypes.push_back(enemy1prot);
	PrototypeManager::AddPrototype("EnemyManager", enemyController);

	GameObject player1EmptyLife = GameObject("Player1EmptyLife");
	sd= player1EmptyLife.AddComponent<SpriteDrawable>();
	player1EmptyLife.position = glm::vec2(-20, 16);
	player1EmptyLife.size = glm::vec2(2, 2);
	sd->sprite = ResourceManager::GetSpritesheet("Knight3").sprites[8];
	sd->drawOrder = 200;
	PrototypeManager::AddPrototype("Player1EmptyLife", player1EmptyLife);

	GameObject player1Life = GameObject("Player1Life");
	sd = player1Life.AddComponent<SpriteDrawable>();
	player1Life.size = glm::vec2(2, 2);
	sd->sprite = ResourceManager::GetSpritesheet("Knight3").sprites[7];
	sd->drawOrder = 201;
	PrototypeManager::AddPrototype("Player1Life", player1Life);

	GameObject player2EmptyLife = GameObject("Player2EmptyLife");
	sd = player2EmptyLife.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[8];
	player2EmptyLife.position = glm::vec2(11, 16);
	player2EmptyLife.size = glm::vec2(2, 2);
	sd->flipped = true;
	sd->drawOrder = 200;
	PrototypeManager::AddPrototype("Player2EmptyLife", player2EmptyLife);

	GameObject player2Life = GameObject("Player2Life");
	player2Life.size = glm::vec2(2, 2);
	sd = player2Life.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[7];
	sd->drawOrder = 201;
	sd->flipped = true;
	PrototypeManager::AddPrototype("Player2Life", player2Life);

	GameObject scoreBoard = GameObject("ScoreBoard");
	ScoreBoard* sbComp=scoreBoard.AddComponent<ScoreBoard>();
	sbComp->lifePrototypes.push_back(&PrototypeManager::GetPrototype("Player1Life"));
	sbComp->lifePrototypes.push_back(&PrototypeManager::GetPrototype("Player2Life"));
	sbComp->emptyPrototypes.push_back(&PrototypeManager::GetPrototype("Player1EmptyLife"));
	sbComp->emptyPrototypes.push_back(&PrototypeManager::GetPrototype("Player2EmptyLife"));
	PrototypeManager::AddPrototype("ScoreBoard", scoreBoard);
	PrototypeManager::GetPrototype("OnionKnight").GetComponent<EnemyKnight>()->value = scoreBoard.GetComponent<ScoreBoard>()->ENEMY_VALUE;
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
		if (InputReader::instance().isButtonDown(GLFW_KEY_ENTER))
		{
			activeLB->SaveScores();
			SetUpMenu();
		}
		break;
	}
}
void GameManager::SetUpMenu()
{
	state = E_GAME_STATE::GAME_MENU;
	game->ClearRoom();
	game->Instantiate(PrototypeManager::GetPrototype("TitleScreen"));
	if (!initDone)
	{
		GameObject* SoundBox = game->Instantiate(PrototypeManager::GetPrototype("MusicBox"));
		SoundBox->GetComponent<AudioSource>()->looping = true;
		SoundBox->GetComponent<AudioSource>()->PlaySound("MainTheme");
	}
	game->Instantiate(PrototypeManager::GetPrototype("StartUI"));
	initDone=true;
}
void GameManager::SetUpActive()
{
	players.clear();
	state = E_GAME_STATE::GAME_PLAYING;
	game->ClearRoom();
	GameObject *player1=game->Instantiate(PrototypeManager::GetPrototype("Player1"));
	player1->position = glm::vec2(0, 0);
	players.push_back(player1->GetComponent<PlayerKnight>());

	GameObject *player2 = game->Instantiate(PrototypeManager::GetPrototype("Player2"));
	player2->position = glm::vec2(0, 0);
	players.push_back(player2->GetComponent<PlayerKnight>());
	player2->GetComponent<PlayerKnight>()->playerNumber = 1;
	player2->SetActive(false);

	GameObject* em=game->Instantiate(PrototypeManager::GetPrototype("EnemyManager"));
	em->GetComponent<EnemyManager>()->players.push_back(player1->GetComponent<PlayerKnight>());
	em->GetComponent<EnemyManager>()->players.push_back(player2->GetComponent<PlayerKnight>());
	game->Instantiate(PrototypeManager::GetPrototype("CoverScreenWhite"));
	game->Instantiate(PrototypeManager::GetPrototype("Platform"))->position = glm::vec2(0, 18);
	game->Instantiate(PrototypeManager::GetPrototype("Platform2"))->position=glm::vec2(15,0);
	game->Instantiate(PrototypeManager::GetPrototype("Platform3"))->position = glm::vec2(-15, 0);
	game->Instantiate(PrototypeManager::GetPrototype("Lava"))->position = glm::vec2(0, 20);
	GameObject *outsideTop=game->Instantiate(PrototypeManager::GetPrototype("Platform"));
	outsideTop->position = glm::vec2(0, -73.0f);
	outsideTop->size = glm::vec2(outsideTop->size.x + 120, outsideTop->size.y);
	GameObject *sb = game->Instantiate(PrototypeManager::GetPrototype("ScoreBoard"));
	sb->GetComponent<ScoreBoard>()->players.push_back(player1->GetComponent<PlayerKnight>());
	sb->GetComponent<ScoreBoard>()->players.push_back(player2->GetComponent<PlayerKnight>());
}

void GameManager::SetUpScoreboard()
{
	int player1Score = players[0]->score, player2Score = players[1]->score;
	game->ClearRoom();
	state = E_GAME_STATE::GAME_SCOREBOARD;
	GameObject* LBHeader = game->Instantiate(PrototypeManager::GetPrototype("LeaderboardHeader"));
	GameObject* Leaderboard= game->Instantiate(PrototypeManager::GetPrototype("Leaderboard"));
	LeaderBoard* LBComp = Leaderboard->GetComponent<LeaderBoard>();
	activeLB = LBComp;
	LBComp->FetchSavedEntries();
	GameObject* GratsMessage = game->Instantiate(PrototypeManager::GetPrototype("CongratsUI"));
	GameObject* NameMessage = game->Instantiate(PrototypeManager::GetPrototype("CongratsUI"));
	GameObject* EnterMessage = game->Instantiate(PrototypeManager::GetPrototype("CongratsUI"));
	EnterMessage->GetComponent<TextUI>()->text = "Press Enter to Continue";
	EnterMessage->GetComponent<TextUI>()->color = glm::vec3(255, 255, 255);
	EnterMessage->GetComponent<TextUI>()->position.y += 100;
	NameMessage->GetComponent<TextUI>()->position.y += 50;

	GameObject* boxName = game->Instantiate(PrototypeManager::GetPrototype("InputBoxLB"));
	GratsMessage->SetActive(false);
	NameMessage->SetActive(false);
	if (player1Score >= player2Score && LBComp->CheckScore(player1Score))
	{
		//Player 1 got a new HighScore!
		LBComp->RegisterNewEntry(player1Score, boxName->GetComponent<InputBox>());
		GratsMessage->GetComponent<TextUI>()->text += "Player 1!";
		GratsMessage->SetActive(true);
		NameMessage->GetComponent<TextUI>()->text = "Type your name";
		NameMessage->SetActive(true);
	}
	else if(LBComp->CheckScore(player2Score))
	{
		//Player 2 got a new HighScore!
		LBComp->RegisterNewEntry(player2Score, boxName->GetComponent<InputBox>());
		GratsMessage->GetComponent<TextUI>()->text += "Player 2!";
		GratsMessage->SetActive(true);
		NameMessage->GetComponent<TextUI>()->text = "Type your name";
		NameMessage->SetActive(true);
	}
	boxName->SetActive(GratsMessage->isActive());
	LBComp->GenerateTextEntries(PrototypeManager::GetPrototype("LeaderboardEntry"));



}

void GameManager::ActivatePlayer2()
{
	if (!players.at(1)->GetOwner()->isActive() && players.at(1)->healthPoints>0)
	{
		players.at(1)->GetOwner()->SetActive(true);
		players.at(1)->GetOwner()->position = glm::vec2(0, 0);
	}
}
