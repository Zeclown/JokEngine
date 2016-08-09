#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H
#include "AnimationFrame"
#include "Animation"
namespace Jokengine
{
	enum E_ANIMATION_PLAYMODE {
		STOP_ALL,STOP_OTHERS
	};
	class SpriteAnimator : public CloneableComponent<Component,SpriteAnimator>
	{
	public:
		void Update();
		void DeleteAnimation(std::string animationName);
		void DeleteFrames(std::string animationName,GLint startFrame,GLint endFrame=std::numeric_limits<GLint>::max());
		void SetFramesDuration(std::string animationName,GLfloat duration,GLint startFrame=0,GLint endFrame=std::numeric_limits<GLint>::max());
		void SetFrameDuration(std::string animationName,GLfloat duration,GLint frameIndex)
		AnimationFrame GetFrame(std::string animationName,GLint frame=0);
		std::vector<AnimationFrame> GetFrames(std::string animationName,GLint startFrame,GLint endFrame);
		void PlayAnimation(std::string animationName,E_ANIMATION_PLAYMODE playmode=E_ANIMATION_PLAYMODE::STOP_OTHERS);
		void AddToQueue(std::string animationName);
	private:
		SpriteDrawable *spriteDraw;
		GLboolean replaying;
		GLfloat timer;
		vector<std::pair<std::string,Animation>> animationQueue;
		map<string,Animation> animations;
		void updateAnimation();

	};
}
#endif