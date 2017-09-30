#ifndef ANIMATION_H
#define ANIMATION_H
#include "AnimationFrame.h"
#include <vector>
#include "SpriteSheet.h"

//the different wrapmodes of an animation (what is the animation doing when it ends and nothing is left in the animation queue)
enum E_ANIMATION_WRAPMODE {
	LOOP, //will loop back from the beginning
	ONCE, //will go back to the first frame and freeze
	CLAMP, //will stay clamped at the last frame
	PINGPONG //will play back the animation in reverse and then in order again, rinse and repeat
};

//Used by SpriteAnimators to store animation data
// Example:
//
// ResourceManager::LoadSpritesheet("sprites/knight_sheet.png", GL_TRUE, glm::vec2(64,64),"Player");
//  SpriteAnimator* sp= gameObject.AddComponent<SpriteAnimator>();
//  sp->AddAnimation(Animation(ResourceManager::GetSpritesheet("Player")), "Idle");
class Animation
{
	enum E_ANIMATION_STATE
	{
		PLAY,PAUSED,REVERSED
	};
	public:
		Animation();
		Animation(std::vector<Sprite> sp,GLfloat frameDuration=0.5f);
		Animation(SpriteSheet sp, GLfloat frameDuration = 0.5f);
		Animation(SpriteSheet sp, GLuint firstFrame, GLuint lastFrame,GLfloat frameDuration = 0.5f);
		//a speed modifier for the animation default = 1f
		GLfloat animationSpeed;
		//The animation wrapmode
		E_ANIMATION_WRAPMODE wrapMode; 
		std::vector<AnimationFrame> frames;
		//ask the animation for the next frame and change the animation's state accordingly
		std::pair<AnimationFrame,GLboolean> GetNextFrame();
	private:
		GLuint frameIndex;
		E_ANIMATION_STATE state;
		//is it currently wrapping?
		GLboolean wrapping;			
};
	

#endif
