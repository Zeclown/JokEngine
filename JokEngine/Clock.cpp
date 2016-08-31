#include "Clock.h"

Clock::Clock()
	:timeScale(1),lastFrame(0),deltaTime(0)
{
		
}
GLfloat Clock::GetDeltaTime()
{
	return deltaTime;
}
GLfloat Clock::GetFPS()
{
	return FPS;
}
GLfloat Clock::GetLastFrame()
{
	return lastFrame;
}
void Clock::UpdateTime(GLfloat time)
{
	deltaTime = time - lastFrame;
	lastFrame = time;
	FPS = 1 / deltaTime;
}
