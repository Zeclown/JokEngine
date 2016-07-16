

#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <memory>
#include <iostream>
#include <vector>
#include "GameObject.h"
namespace Jokengine
{

	//Singleton class where all the GameObjects currently in the game are. This is a "scene".
	class GameRoom
	{
	public:
		static GameRoom& instance() 
		{ 
			if (!instance_)
				instance_ = new GameRoom;
			return *instance_; 
		}
		std::weak_ptr<GameObject> Instantiate(GameObject &toInstantiate);
		//all the objects in the GameRoom
		std::vector<std::shared_ptr<GameObject>> RoomObjects;
	private:
		static GameRoom *instance_;
		GameRoom() { }

	};

}
#endif