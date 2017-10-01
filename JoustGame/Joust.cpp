#include "JokEngine.h"
#include "GameManager.h"

void LoadResources()
{
	ResourceManager::LoadSprite("sprites/ground.png", false, "Cover");
	ResourceManager::LoadSpritesheet("sprites/Knight1.png", true,glm::vec2(64,64), "Knight1");
	ResourceManager::LoadSpritesheet("sprites/Knight2.png", true, glm::vec2(64, 64), "Knight2");
	ResourceManager::LoadSpritesheet("sprites/Knight3.png", true, glm::vec2(64, 64), "Knight3");
	ResourceManager::LoadSprite("sprites/TitleScreen.png", true, "TitleScreen");
	ResourceManager::LoadSprite("sprites/Platform.png", true, "Platform");
	ResourceManager::LoadSprite("sprites/Lava.png", false, "Lava");
	ResourceManager::LoadSprite("sprites/Platform2.png", true, "Platform2");
	ResourceManager::LoadSprite("sprites/Platform3.png", true, "Platform3");
	ResourceManager::LoadSprite("sprites/Egg.png", true, "Egg");
	ResourceManager::LoadAudioFile("sounds/song.wav", "MainTheme");
}
int main()
{
	Game& game = Game::GetInstance();
	game.Init();
	LoadResources();
	game.Instantiate(GameObject("Manager"))->AddComponent<GameManager>();
	game.Loop();
}
