#include "Animation.h"
namespace Jokengine
{
	Animation::Animation()
		:animationSpeed(1),wrapMode(E_ANIMATION_WRAPMODE::LOOP),state(E_ANIMATION_STATE::PLAY)
	{
	}
	Animation::Animation(std::vector<Sprite> sp, GLfloat frameDuration)
		: Animation()
	{
		for (int i = 0; i < sp.size(); i++)
		{
			frames.push_back(AnimationFrame(sp[i], frameDuration));
		}

	}
	Animation::Animation(SpriteSheet sp, GLfloat frameDuration)
		:Animation(sp.sprites, frameDuration)
	{	
	}
	std::pair<AnimationFrame,GLboolean> Animation::GetNextFrame()
	{
		if(frameIndex>=frames.size())//Now in wrapping mode if we are not already. Decides what to do next since there is not more next frame to use
		{
			wrapping=true;
			switch(wrapMode)
			{
				case E_ANIMATION_WRAPMODE::LOOP:
					frameIndex=0;
					state=E_ANIMATION_STATE::PLAY;
					break;
				case E_ANIMATION_WRAPMODE::ONCE :
					frameIndex=0;
					state=E_ANIMATION_STATE::PAUSED;
					break;
				case E_ANIMATION_WRAPMODE::PINGPONG :
					frameIndex=frames.begin()-frames.end();
					state=E_ANIMATION_STATE::REVERSED;
					break;
				case E_ANIMATION_WRAPMODE::CLAMP : 
					frameIndex=frames.begin()-frames.end();
					state=E_ANIMATION_STATE::PAUSED;
					break;
				 
					
			}
		}
		std::pair<AnimationFrame,std::string> nextFrame;
		nextFrame.first=frames[frameIndex];
		switch(state)//ready up the next frame index
		{
			case E_ANIMATION_STATE::PLAY :
				frameIndex++;
				break;
			case E_ANIMATION_STATE::REVERSED :
				if(wrapMode==E_ANIMATION_WRAPMODE::PINGPONG)//just in case, as I am writing this comment, this should always return true, there is no other way to reverse an animation
				{
					if(frameIndex==0)//we turn back around and play the animation in order
					{
						state = E_ANIMATION_STATE::PLAY;
						frameIndex++;
					}
					else
						frameIndex--;
				}
				break;
		}
		return std::pair<AnimationFrame, GLboolean>(nextFrame.first, wrapping);
	}
}