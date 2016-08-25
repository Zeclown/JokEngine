#include "SpriteAnimator.h"
namespace Jokengine
{
void SpriteAnimator::Update()
{
	if(animationQueue.size()>0)
	{
		timer+=Game::GetInstance().GetTimeService().GetDeltaTime()*animationQueue[0].animationSpeed;
		if(!nextFrame || timer>currentFrame.second.duration)//is it time for a next frame
		{
			timer=0;
			std::pair<AnimationFrame,GLboolean> nextFrame=animationQueue[0].GetNextFrame();
			while(nextFrame.second && animationQueue.size()>1) //find the next animation or settle for the last wrapped one
			{
				animationQueue.erase(0);
				nextFrame=animationQueue[0].GetNextFrame();
			}
			spriteDraw->sprite=nextFrame.first.sprite;
			currentFrame=nextFrame;
		}
	}
}

void SpriteAnimator::Init()
{
	spriteDraw = owner->GetComponent<SpriteDrawable>();
	if(!spriteDraw)
	{
		spriteDraw = owner->AddComponent<SpriteDrawable>();
	}
}
void SpriteAnimator::AddAnimation(Animation animation,std::string animationName)
{
	animations[animationName]=animation;
}
void SpriteAnimator::DeleteAnimation(std::string animationName)
{
	animations.erase(animationName);
}
void SpriteAnimator::PlayAnimation(std::string animationName,E_ANIMATION_PLAYMODE playmode)
{
	if(animationQueue.size==0 || animationQueue[0].first!=animationName || playmode==E_ANIMATION_PLAYMODE::STOP_ALL)
	{
		animationQueue.insert(animationQueue.begin(),std::make_pair(animationName,animations[animationName]));	
	}
}
void SpriteAnimator::AddToQueue(std::string animationName)
{
	animationQueue.push_back(std::make_pair(animationName,animations[animationName]));
}
}