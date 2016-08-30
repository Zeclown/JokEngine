

#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <memory>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include <map>
namespace Jokengine
{

	//Singleton class where all the GameObjects currently in the game are. This is a "scene". It is contained in Game and shouldn't be used directly
	class GameRoom
	{
	public:
		static GameRoom& instance() 
		{ 
			if (!instance_)
				instance_ = new GameRoom;
			return *instance_; 
		}

		GameObject* Instantiate(GameObject &toInstantiate);
		void Destroy(GameObject &toDestroy,GLfloat after);
		void CleanUpResources();
		//all the objects in the GameRoom
		std::map<GLint,std::shared_ptr<GameObject>> RoomObjects;
		GameObject* FindByID(GLint id);
		/*void CheckDestroyQueue();*/
	private:
		void DestroyObject(GameObject &toDestroy);
		static GameRoom *instance_;
		int idCount;
		GameRoom();

	};

}
#endif