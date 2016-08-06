#ifndef SPRITEDRAWABLE_H
#define SPRITEDRAWABLE_H
#include "Texture.h"
#include "SpriteRenderingService.h"
#include "Component.h"
#include "Sprite.h"
namespace Jokengine
{
	// Component that store a sprite and ask the SpriteRenderer to draw it every frame
	// Exemple:
	//
	//  RessourceManager::LoadTexture("textures/goblin.png",GL_TRUE,"goblin")
	//	GameObject go= GameObject();
	//	go.AddComponent<SpriteRenderer>();
	//  go.sprite=ResourceManager::GetTexture("goblin");
	class SpriteDrawable :public ComponentCloneable<Component,SpriteDrawable> {
	public:
		SpriteDrawable(GameObject* gameObject);
		Sprite sprite;
		glm::vec3   color;
		// Draw sprite
		virtual void Draw(SpriteRenderingService &renderer,glm::vec2 intrapolation);

	};
}
#endif