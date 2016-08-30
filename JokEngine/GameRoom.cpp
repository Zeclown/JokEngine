#include"GameRoom.h"
#include"Game.h"
#include <boost/signals2/signal.hpp>
// added specializations for std::weak_ptr and std::shared_ptr

namespace Jokengine
{

	GameRoom *GameRoom::instance_ = 0;
	GameRoom::GameRoom()
		:idCount(0)
	{

	}

	GameObject* GameRoom::Instantiate(GameObject &toInstantiate) {
		
		std::shared_ptr<GameObject> objPtr = std::make_shared<GameObject>(toInstantiate);
		objPtr->objectID = ++idCount;
		RoomObjects[objPtr->objectID] = objPtr;
		Game::GetInstance().initSignal.connect(boost::signals2::signal<void()>::slot_type(&GameObject::Init,objPtr.get()).track_foreign(objPtr) );
		return objPtr.get();
	}
	void GameRoom::Destroy(GameObject & toDestroy, GLfloat after)
	{
		if (RoomObjects.count(toDestroy.objectID) > 0)
		{
			RoomObjects[toDestroy.objectID]->Destroy(after);
		}
	}
	void GameRoom::CleanUpResources()
	{
		for (std::map<GLint, std::shared_ptr<GameObject>>::iterator iter = RoomObjects.begin(); iter != RoomObjects.end();)
		{
			if (iter->second->CheckDestroy(Game::GetInstance().GetTimeService().GetDeltaTime()))
			{
				
				DestroyObject(*iter->second);
				iter = RoomObjects.begin();
			}
			else
			{
				for (int j = 0; j < iter->second->components.size(); j++)
				{
					if (iter->second->components[j]->CheckDestroy(Game::GetInstance().GetTimeService().GetDeltaTime()))
					{
						delete iter->second->components[j];
						iter->second->components.erase(iter->second->components.begin() + j);
						j--;
					}
				}
				iter++;
			}
			
		}
	}

	GameObject* GameRoom::FindByID(GLint id)
	{
		if (RoomObjects.count(id) > 0)
			return RoomObjects[id].get();
		else
			return nullptr;
	}
	void GameRoom::DestroyObject(GameObject &toDestroy)
	{
		for (int i = 0; i < toDestroy.children.size(); i++)//recursively destroys all the hierarchy beneath the object
		{
			DestroyObject(*toDestroy.children[i]);
		}
		RoomObjects.erase(toDestroy.objectID);
	}
}