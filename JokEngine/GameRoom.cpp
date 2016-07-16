#include"GameRoom.h"
namespace Jokengine
{
	GameRoom *GameRoom::instance_ = 0;
	std::weak_ptr<GameObject> GameRoom::Instantiate(GameObject &toInstantiate) {
		std::shared_ptr<GameObject> objPtr = std::make_shared<GameObject>(toInstantiate);
		RoomObjects.push_back(objPtr);
		std::weak_ptr<GameObject> toReturn = objPtr;
		return toReturn;
	}
}