

#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <memory>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include <map>
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
		std::map<GLint,std::shared_ptr<GameObject>> RoomObjects;
		std::weak_ptr<GameObject> FindByID(GLint id);
	private:
		static GameRoom *instance_;
		int idCount;
		GameRoom();

	};

}
#endif