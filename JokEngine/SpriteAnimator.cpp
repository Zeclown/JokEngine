#include "SpriteAnimator.h"
void SpriteAnimator::AddFrame(string animationName,Sprite sprite,GLfloat duration)
{

}
void SpriteAnimator::Update()
{
	
}
void SpriteAnimator::Init()
{
	spriteDraw = owner->GetComponent<SpriteDrawable>();
	if(!spriteDraw)
	{
		spriteDraw = owner->AddComponent<SpriteDrawable>();
	}
}
void SpriteAnimator::AddAnimation(string animationName,Animation animation)
{
	animations[animationName]=animation;
}
void SpriteAnimator::DeleteAnimation(string animationName)
{
	animations.erase(animationName);
}
void SpriteAnimator::DeleteFrames(string animationName,GLint startFrame,GLint endFrame)
{
	if(endFrame>=animations[animationName].frames.size())
		endFrame=animations[animationName].frames.size()-1;
	 myvector.erase (animations[animationName].frames.begin()+startFrame,animations[animationName].frames.begin()+endFrame);
}
void SpriteAnimator::SetFrameDuration(string animationName,GLfloat duration,GLint frameIndex)
{
	animations[animationName].frames[frameIndex].duration=duration;
}
void SpriteAnimator::SetFramesDuration(string animationName,GLfloat duration,GLint startFrame,GLint endFrame)
{

}
AnimationFrame SpriteAnimator::GetFrame(string animationName,GLint frame)
{
	return animations[animationName].frames[frame];
}
std::vector<AnimationFrame> SpriteAnimator::GetFrames(string animationName,GLint startFrame,GLint endFrame)
{
	if(endFrame>=animations[animationName].frames.size())
		endFrame=animations[animationName].frames.size()-1;
	std::vector<AnimationFrame> toReturn(animations[animationName].frames.begin()+startFrame,animations[animationName].frames.begin()+endFrame);
	return toReturn;	
}
void SpriteAnimator::PlayAnimation(string animationName)
{

}
void SpriteAnimator::AddToQueue(string animationName)
{

}
void SpriteAnimator::updateAnimation()
{

}