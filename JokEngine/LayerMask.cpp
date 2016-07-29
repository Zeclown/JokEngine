#include "LayerMask.h"
namespace Jokengine
{
	LayerMask::LayerMask(uint16 categoryBits,uint16 maskBits)
	 :categoryBits(categoryBits),maskBits(maskBits|0x0001)
	{
		
	}
}