#include "SpriteDrawable.h"
#include "GameObject.h"


SpriteDrawable::SpriteDrawable(GameObject* gameObject)
	:ComponentCloneable(gameObject),color(glm::vec3(1,1,1))
{

}
void SpriteDrawable::Draw(SpriteRenderingService &renderer, glm::vec2 intrapolation)
{
	renderer.DrawSprite(sprite,GetOwner()->GetWorldPosition() - intrapolation, GetOwner()->GetWorldSize(), GetOwner()->GetWorldRotation(),color);
}
