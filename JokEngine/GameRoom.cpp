#include"GameRoom.h"
namespace Jokengine
{
	GameRoom *GameRoom::instance_ = 0;
	GameRoom::GameRoom()
		:idCount(0)
	{

	}
	std::weak_ptr<GameObject> GameRoom::Instantiate(GameObject &toInstantiate) {
		toInstantiate.objectID = ++idCount;
		std::shared_ptr<GameObject> objPtr = std::make_shared<GameObject>(toInstantiate);
		RoomObjects[toInstantiate.objectID]=objPtr;
		std::weak_ptr<GameObject> toReturn = objPtr;
		return toReturn;
	}
	std::weak_ptr<GameObject> GameRoom::FindByID(GLint id)
	{
		if (RoomObjects.count(id) > 0)
			return RoomObjects[id];
		else
			return std::weak_ptr<GameObject>();
	}
}