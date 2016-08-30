#ifndef ANIMATION_H
#define ANIMATION_H
#include "AnimationFrame.h"
namespace Jokengine
{
	enum E_ANIMATION_WRAPMODE {
		LOOP,ONCE,CLAMP,PINGPONG
	};

	class Animation
	{
		enum E_ANIMATION_STATE
		{
			PLAY,PAUSED,REVERSED
		};
		public:
			Animation();
			GLfloat animationSpeed;
			E_ANIMATION_WRAPMODE wrapMode; 
			std::vector<AnimationFrame> frames;
			std::pair<AnimationFrame,GLboolean> GetNextFrame();
		private:
			GLint frameIndex;
			E_ANIMATION_STATE state;
			GLboolean wrapping;			
	};
	
}
#endif