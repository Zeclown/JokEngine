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
void GameManager::Init()
{
	owner->Update.connect(boost::bind(&GameManager::Update, this));


	game = &Game::GetInstance();
	//Make sure the game manager is not destroyed while the game still runs
	owner->dontDestroyOnClean = true;
	//START MENU PROTOTYPES INIT
	GameObject titleScreen = GameObject("Title Screen");
	titleScreen.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSprite("TitleScreen");
	titleScreen.size = glm::vec2(220, 130);
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
	txt->position = glm::vec2(-173, 200);
	txt->scale = 1;
	txt->text = "Press Any Key";
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
	player.AddComponent<PhysicBody>()->SetDrag(1.0f);
	player.GetComponent<PhysicBody>()->SetFreezeRotation(true);
	player.AddComponent<CircleCollider>();
	player.AddComponent<PlayerKnight>();
	player.AddComponent<InputHandler>();
	player.AddComponent<SpriteDrawable>()->sprite = ResourceManager::GetSpritesheet("Knight1").sprites[1];
	player.GetComponent<SpriteDrawable>()->drawOrder = 1;
	Animation anim = Animation(ResourceManager::GetSpritesheet("Knight1"),0,1);
	anim.wrapMode = E_ANIMATION_WRAPMODE::LOOP;
	player.AddComponent<SpriteAnimator>()->AddAnimation(anim,"Idle");
	Animation anim2 = Animation(ResourceManager::GetSpritesheet("Knight1"), 2, 5,0.1f);
	player.GetComponent<SpriteAnimator>()->AddAnimation(anim2, "Running");
	player.size = glm::vec2(14, 14);
	prefabs.insert(std::map< std::string, GameObject >::value_type("Player1", player));

	GameObject OutsideBoundVertical = GameObject("VerticalBound");
	OutsideBoundVertical.AddComponent<PhysicBody>()->SetKinematic(true);
	sd = OutsideBoundVertical.AddComponent<SpriteDrawable>();
	sd->sprite = ResourceManager::GetSprite("Platform");
	OutsideBoundVertical.AddComponent<BoxCollider>()->size.y=0.5f;
	OutsideBoundVertical.size = glm::vec2(40, 13);
	prefabs.insert(std::map< std::string, GameObject >::value_type("OutsideBoundVertical", OutsideBoundVertical));
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
	state = E_GAME_STATE::GAME_PLAYING;
	game->ClearRoom();
	game->Instantiate(prefabs.find("Player1")->second)->position=glm::vec2(0,0);
	game->Instantiate(prefabs.find("CoverScreenWhite")->second);
	game->Instantiate(prefabs.find("OutsideBoundVertical")->second)->position=glm::vec2(0,50.0f);
	game->Instantiate(prefabs.find("OutsideBoundVertical")->second)->position = glm::vec2(0, -72.0f);
}
