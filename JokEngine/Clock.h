#ifndef CLOCK_H
#define CLOCK_H
#include "TimeService.h"
namespace Jokengine
{
	class Clock : public TimeService
	{
	public:
		Clock();
		GLfloat timeScale;
		virtual void UpdateTime(GLfloat time);
		virtual GLfloat GetDeltaTime() ;
		virtual GLfloat GetLastFrame() ;
		virtual GLfloat GetFPS() ;
	private:
		GLfloat deltaTime;
		GLfloat lastFrame;
		GLfloat FPS;
	};
}
#endif
