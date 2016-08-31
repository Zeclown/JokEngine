#ifndef PHYSICAL_LAYER_H
#define PHYSICAL_LAYER_H
#include <string>
#include "Box2D\Dynamics\b2Body.h"

class PhysicLayer
{
	public:
			PhysicLayer(uint16 categoryBits=0x0001, uint16 maskBits=-1);
			uint16 categoryBits;
			uint16 maskBits;
			std::string name;
};

#endif