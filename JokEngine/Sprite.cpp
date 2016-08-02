#include "Sprite.h"
namespace Jokengine
{
	Sprite::Sprite(Texture2D *texture,std::array<glm::vec2,6> textureCoords)
	:texture(texture),textureCoords(textureCoords)
	{
	
	}
	Sprite::Sprite(Texture2D *texture)
	:texture(texture)
	{
		std::array<glm::vec2,6> defaultArray={glm::vec2(0.0f, 1.0f),glm::vec2(1.0f, 0.0f),glm::vec2(0.0f, 0.0f),
											  glm::vec2(0.0f, 1.0f),glm::vec2(1.0f, 1.0f),glm::vec2(1.0f, 0.0f)};
		textureCoords=defaultArray;
									
	}
}