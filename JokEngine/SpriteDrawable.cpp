#include "SpriteDrawable.h"
#include "GameObject.h"
namespace Jokengine
{

	SpriteDrawable::SpriteDrawable(Texture2D sprite,glm::vec3 color)
		:sprite(sprite),color(color)
	{

	}
	void SpriteDrawable::Draw(SpriteRenderingService &renderer, glm::vec2 intrapolation)
	{
		renderer.DrawSprite(sprite,owner->position- intrapolation,owner->size,owner->rotation,color);
	}
}