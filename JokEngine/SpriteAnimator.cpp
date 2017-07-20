#include "SpriteAnimator.h"
#include "Game.h";

SpriteAnimator::SpriteAnimator(GameObject * gameObject)
	:ComponentCloneable(gameObject)
{
}
void SpriteAnimator::Update()
{
	if (spriteDraw)
	{
		if (animationQueue.size() > 0)
		{

			timer += Game::GetInstance().GetTimeService().GetDeltaTime()*animationQueue[0].second.animationSpeed;
			if (timer > currentFrame.first.duration || bFirstPlay)//is it time for a next frame
			{
				timer = 0;
				bFirstPlay = false;
				std::pair<AnimationFrame, GLboolean> nextFrame = animationQueue[0].second.GetNextFrame();
				while (nextFrame.second && animationQueue.size() > 1) //find the next animation or settle for the last wrapped one
				{
					animationQueue.erase(animationQueue.begin());
					nextFrame = animationQueue[0].second.GetNextFrame();
				}
				spriteDraw->sprite = nextFrame.first.sprite;
				currentFrame = nextFrame;
			}
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
	if(animationQueue.size()==0 || animationQueue[0].first!=animationName || playmode==E_ANIMATION_PLAYMODE::STOP_ALL)
	{
		animationQueue.clear();
		bFirstPlay = true;
		animationQueue.insert(animationQueue.begin(),std::make_pair(animationName,animations[animationName]));	
		Update();
	}
	
}
void SpriteAnimator::AddToQueue(std::string animationName)
{
	animationQueue.push_back(std::make_pair(animationName,animations[animationName]));
}
