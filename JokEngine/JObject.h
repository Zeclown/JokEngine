#ifndef JOBJECT_H
#define JOBJECT_H
#include <GL/glew.h>
namespace Jokengine
{
	// Base class of every object in JokEngine
	class JObject {
	public:
		JObject() {};
		virtual void Destroy(GLfloat time = 0);
	private:
		GLboolean markedToDestroy;
		GLfloat toDestroyTimer;

	};
}
#endif