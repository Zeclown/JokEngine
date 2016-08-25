#include "SpriteAnimator.h"
void SpriteAnimator::AddFrame(string animationName,Sprite sprite,GLfloat duration)
{

}
void SpriteAnimator::Update()
{
	if(animationQueue.size()>0)
	{
		std::pair<AnimationFrame,GLboolean> nextFrame=animationQueue[0].GetNextFrame();
		while(nextFrame.second || animationQueue.size()>1) //find the next animation or settle for the wrapped one
		{
			animationQueue.erase(0);
			nextFrame=animationQueue[0].GetNextFrame();
		}
		spriteDraw->sprite=nextFrame.first.sprite;
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
void SpriteAnimator::AddAnimation(std::string animationName,Animation animation)
{
	animations[animationName]=animation;
}
void SpriteAnimator::DeleteAnimation(std::string animationName)
{
	animations.erase(animationName);
}
void SpriteAnimator::DeleteFrames(std::string animationName,GLint startFrame,GLint endFrame)
{
	if(endFrame>=animations[animationName].frames.size())
		endFrame=animations[animationName].frames.size()-1;
	 myvector.erase (animations[animationName].frames.begin()+startFrame,animations[animationName].frames.begin()+endFrame);
}
void SpriteAnimator::SetFrameDuration(std::string animationName,GLfloat duration,GLint frameIndex)
{
	animations[animationName].frames[frameIndex].duration=duration;
}
void SpriteAnimator::SetFramesDuration(std::string animationName,GLfloat duration,GLint startFrame,GLint endFrame)
{
	if(endFrame>=animations[animationName].frames.size())
		endFrame=animations[animationName].frames.size()-1;
	for(auto iter = animations[animationName].frames.begin+startFrame;iter!=animations[animationName].frames.begin+endFrame;iter++)
	{
		iter->duration=duration
	}
}
AnimationFrame SpriteAnimator::GetFrame(std::string animationName,GLint frame)
{
	return animations[animationName].frames[frame];
}
std::vector<AnimationFrame> SpriteAnimator::GetFrames(std::string animationName,GLint startFrame,GLint endFrame)
{
	if(endFrame>=animations[animationName].frames.size())
		endFrame=animations[animationName].frames.size()-1;
	std::vector<AnimationFrame> toReturn(animations[animationName].frames.begin()+startFrame,animations[animationName].frames.begin()+endFrame);
	return toReturn;	
}
void SpriteAnimator::PlayAnimation(std::std::string animationName,E_ANIMATION_PLAYMODE playmode)
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
