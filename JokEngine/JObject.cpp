#include "JObject.h"
namespace Jokengine
{
	JObject::~JObject()
	{

	}
	void JObject::Destroy(GLfloat time)
	{
		markedToDestroy = true;
		toDestroyTimer = time;
	}
	GLboolean JObject::CheckDestroy(GLfloat dt)
	{
		toDestroyTimer -= dt;
		if (markedToDestroy && toDestroyTimer <= 0)
		{
			return true;
		}
		return false;
	}
}