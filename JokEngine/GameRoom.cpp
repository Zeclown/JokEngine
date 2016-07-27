#include"GameRoom.h"
#include"Game.h"
#include <boost/signals2/signal.hpp>
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
		Game::GetInstance().initSignal.connect(boost::signals2::signal<void()>::slot_type(&GameObject::Init,objPtr.get(),_1).track_foreign(objPtr) );
		return objPtr.get();
	}
	GameObject* GameRoom::FindByID(GLint id)
	{
		if (RoomObjects.count(id) > 0)
			return RoomObjects[id].get();
		else
			return nullptr;
	}
}