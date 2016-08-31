#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include <gl\glew.h>

//Time Service that holds information about Timers and is updated each frame
class TimeService
{
public:
	virtual void UpdateTime(GLfloat time) = 0;
	virtual GLfloat GetDeltaTime() = 0;
	virtual GLfloat GetLastFrame() = 0;
	virtual GLfloat GetFPS() = 0;
};

#endif
