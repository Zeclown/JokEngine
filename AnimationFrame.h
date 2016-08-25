#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H
namespace Jokengine
{
	class AnimationFrame
	{
		public:
			AnimationFrame(Sprite sprite,GLfloat duration);
			Sprite sprite;
			GLfloat duration;
			
	};
}


#endif