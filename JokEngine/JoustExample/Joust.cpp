#include "JokEngine.h"
#include "GameManager.h"

void LoadResources()
{
	ResourceManager::LoadSprite("sprites/ground.png", false, "Cover");
	ResourceManager::LoadSpritesheet("sprites/Knight1.png", true,glm::vec2(64,64), "Knight1");
	ResourceManager::LoadSprite("sprites/TitleScreen.png", true, "TitleScreen");
	ResourceManager::LoadSprite("sprites/Platform.png", true, "Platform");
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
