#include "SpriteDrawable.h"
#include "GameObject.h"
namespace Jokengine
{

	SpriteDrawable::SpriteDrawable(GameObject* gameObject)
		:ComponentCloneable(gameObject)
	{

	}
	void SpriteDrawable::Draw(SpriteRenderingService &renderer, glm::vec2 intrapolation)
	{
		renderer.DrawSprite(sprite,GetOwner()->position- intrapolation, GetOwner()->size, GetOwner()->rotation,color);
	}
}