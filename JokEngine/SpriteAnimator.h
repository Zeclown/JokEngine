#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H
#include "AnimationFrame"
#include "Animation"
namespace Jokengine
{
	class SpriteAnimator : public CloneableComponent<Component,SpriteAnimator>
	{
	public:
		void Update();
		void DeleteAnimation(string animationName);
		void DeleteFrames(string animationName,GLint startFrame,GLint endFrame=std::numeric_limits<GLint>::max());
		void SetFramesDuration(string animationName,GLfloat duration,GLint startFrame=0,GLint endFrame=std::numeric_limits<GLint>::max());
		void SetFrameDuration(string animationName,GLfloat duration,GLint frameIndex)
		AnimationFrame GetFrame(string animationName,GLint frame=0);
		std::vector<AnimationFrame> GetFrames(string animationName,GLint startFrame,GLint endFrame);
		void PlayAnimation(string animationName);
		void AddToQueue(string animationName);
	private:
		SpriteDrawable *spriteDraw;
		GLfloat timer;
		GLint currentAnimIndex;
		vector<Animation> animationQueue;
		map<string,Animation> animations;
		void updateAnimation();

	};
}
#endif