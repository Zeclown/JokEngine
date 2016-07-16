#ifndef SPRITEDRAWABLE_H
#define SPRITEDRAWABLE_H
#include "Texture.h"
#include "SpriteRenderingService.h"
#include "Component.h"
namespace Jokengine
{
	// Component that store a sprite and ask the SpriteRenderer to draw it every frame
	// Exemple:
	//
	//  RessourceManager::LoadTexture("textures/goblin.png",GL_TRUE,"goblin")
	//	GameObject go= GameObject();
	//	go.AddComponent<SpriteRenderer>();
	//  go.sprite=ResourceManager::GetTexture("goblin");
	class SpriteDrawable :public Component {
	public:
		SpriteDrawable() {};
		SpriteDrawable(Texture2D sprite, glm::vec3 color = glm::vec3(0, 0, 0));
		Texture2D sprite;
		glm::vec3   color;
		// Draw sprite
		virtual void Draw(SpriteRenderingService &renderer,glm::vec2 intrapolation);

	};
}
#endif