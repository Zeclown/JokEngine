#ifndef SPRITE_RENDERING_SERVICE_H
#define SPRITE_RENDERING_SERVICE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"

class Shader;
class Texture2D;
//A sprite rendering service
//It draws every active spritedrawable each frame 
class SpriteRenderingService
{
public:
	virtual void DrawSprite(Sprite &sprite, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec4 color = glm::vec4(1.0f))=0;
};

#endif