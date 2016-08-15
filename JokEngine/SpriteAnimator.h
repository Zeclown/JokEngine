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
		void AddAnimation(Animation animation,std::string animationName);
		void DeleteAnimation(std::string animationName);
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