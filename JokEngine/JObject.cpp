#include "JObject.h"

JObject::~JObject()
{

}
JObject::JObject()
	:toDestroyTimer(0),markedToDestroy(false)
{
}
void JObject::Destroy(GLfloat time)
{
	markedToDestroy = true;
	toDestroyTimer = time;
}
GLboolean JObject::CheckDestroy(GLfloat dt)
{
	if(markedToDestroy)
		toDestroyTimer -= dt;
	return markedToDestroy && toDestroyTimer <= 0;

}
