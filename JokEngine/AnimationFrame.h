#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H
#include <Sprite.h>
namespace Jokengine
{
	class AnimationFrame
	{
		public:
			AnimationFrame() {};
			AnimationFrame(Sprite sprite,GLfloat duration);
			Sprite sprite;
			GLfloat duration;
			
	};
}


#endif