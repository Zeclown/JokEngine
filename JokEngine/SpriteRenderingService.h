#ifndef SPRITE_RENDERING_SERVICE_H
#define SPRITE_RENDERING_SERVICE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Jokengine
{
	class Shader;
	class Texture2D;
	class SpriteRenderingService
	{
	public:


		virtual void DrawSprite(Texture2D &texture, glm::vec2 position,
			glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
			glm::vec3 color = glm::vec3(1.0f))=0;
	};
}
#endif