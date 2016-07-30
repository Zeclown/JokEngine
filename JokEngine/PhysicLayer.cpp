#include "PhysicLayer.h"

namespace Jokengine
{
	PhysicLayer::PhysicLayer(uint16 categoryBits, uint16 maskBits)
	 :categoryBits(categoryBits),maskBits(maskBits|0x0001),name("empty")
	{
		
	}
}