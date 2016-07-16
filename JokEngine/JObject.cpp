#include "JObject.h"
namespace Jokengine
{
	void JObject::Destroy(GLfloat time)
	{
		markedToDestroy = true;
		toDestroyTimer = time;
	}
}