#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H
#include <Sprite.h>

//Basic Class used by animations to store data
class AnimationFrame
{
	public:
		AnimationFrame() {};
		AnimationFrame(Sprite sprite,GLfloat duration);
		//the sprite used for the frame
		Sprite sprite;
		//frame's duration in seconds
		GLfloat duration;
			
};



#endif