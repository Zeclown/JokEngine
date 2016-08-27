#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H
#include <Sprite.h>
namespace Jokengine
{
	class AnimationFrame
	{
		public:
			AnimationFrame() {};
			AnimationFrame(Sprite sprite,GLfloat duration=0.5f);
			Sprite sprite;
			GLfloat duration;
			
	};
}


#endif