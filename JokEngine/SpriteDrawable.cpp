#include "SpriteDrawable.h"
#include "GameObject.h"


SpriteDrawable::SpriteDrawable(GameObject* gameObject)
	:ComponentCloneable(gameObject), color(glm::vec4(1.0f)), drawOrder(0)
{

}
void SpriteDrawable::Draw(SpriteRenderingService &renderer, glm::vec2 intrapolation)
{
	sprite.flipped = flipped;
	renderer.DrawSprite(sprite,GetOwner()->GetWorldPosition() - intrapolation, GetOwner()->GetWorldSize(), GetOwner()->GetWorldRotation(),color);
}
