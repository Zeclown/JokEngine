#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H
namespace Jokengine
{
	class AnimationFrame
	{
		public:
			AnimationFrame(Sprite sprite,GLfloat duration=0.5f);
			Sprite sprite;
			GLfloat duration;
			
	};
}


#endif