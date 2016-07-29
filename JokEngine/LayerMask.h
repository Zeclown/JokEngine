#ifndef PHYSIC_LAYER_H
#define PHYSIC_LAYER_H
namespace Jokengine
{
	class PhysicLayer
	{
		public:
				PhysicLayer(uint16 categoryBits=0x0001,uint16 maskBits=0x0001);
				uint16 categoryBits;
				uint16 maskBits;
				string name;
	}
}
#endif