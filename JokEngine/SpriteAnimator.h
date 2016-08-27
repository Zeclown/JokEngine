#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H
#include "AnimationFrame.h"
#include "Animation.h"
#include "Component.h"
#include "SpriteDrawable.h"
#include <vector>
#include <map>
namespace Jokengine
{
	enum E_ANIMATION_PLAYMODE {
		STOP_ALL,STOP_OTHERS
	};
	class SpriteAnimator : public ComponentCloneable<Component,SpriteAnimator>
	{
	public:
		void Update();
		void AddAnimation(Animation animation,std::string animationName);
		void DeleteAnimation(std::string animationName);
		void PlayAnimation(std::string animationName,E_ANIMATION_PLAYMODE playmode=E_ANIMATION_PLAYMODE::STOP_OTHERS);
		void AddToQueue(std::string animationName);
		void Init();
	private:
		SpriteDrawable *spriteDraw;
		GLboolean replaying;
		GLfloat timer;
		std::pair<AnimationFrame,GLboolean> currentFrame;
		std::vector<std::pair<std::string,Animation>> animationQueue;
		std::map<std::string,Animation> animations;


	};
}
#endif