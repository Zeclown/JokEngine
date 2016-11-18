#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "Component.h"
#include "Game.h"
#include "PlayerKnight.h"
enum E_GAME_STATE
{
	GAME_PLAYING,
	GAME_PAUSED,
	GAME_MENU,
	GAME_SCOREBOARD
};
class GameManager : public ComponentCloneable<Component,GameManager>
{
	using ComponentCloneable<Component, GameManager>::ComponentCloneable;
public:

	void Init();
	void Update();
	void SetUpMenu();
	void SetUpMainGame();
	void SetUpActive();
	void SetUpScoreboard();
	void ActivatePlayer2();
	std::map<std::string,GameObject> prefabs;
	Game *game;
	E_GAME_STATE state;
	std::vector<PlayerKnight*> players;




};
#endif // !GAME_MANAGER_H

