#include "SpriteDrawable.h"
#include "GameObject.h"
namespace Jokengine
{

	SpriteDrawable::SpriteDrawable(std::weak_ptr<GameObject> gameObject)
		:Component(gameObject)
	{

	}
	void SpriteDrawable::Draw(SpriteRenderingService &renderer, glm::vec2 intrapolation)
	{
		renderer.DrawSprite(sprite,GetOwner()->position- intrapolation, GetOwner()->size, GetOwner()->rotation,color);
	}
}