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
	//Component that changes the sprite on a sprite drawable
	//It uses a queue system to determine which animation to play
	class SpriteAnimator : public ComponentCloneable<Component,SpriteAnimator>
	{
	public:
		SpriteAnimator(GameObject* gameObject);
		void Update();
		//Register a new animation in the animator and assign it a name
		void AddAnimation(Animation animation,std::string animationName);
		//Unregister an animation by name
		void DeleteAnimation(std::string animationName);
		//Immediately clearing the queue and playing the animation, if playmode=STOP_OTHERS and the same animation is already playing, it will not be interrupted
		void PlayAnimation(std::string animationName,E_ANIMATION_PLAYMODE playmode=E_ANIMATION_PLAYMODE::STOP_OTHERS);
		//Add an animation to the queue
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