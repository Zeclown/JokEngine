#ifndef SPRITE_H
#define SPRITE_H
namespace Jokengine
{
class Sprite
	{
		public:
			Sprite(Texture2D *texture);
			Sprite(Texture2D *texture, std::array<glm::vec2,6> textureCoords);
			Texture2D *texture;
			std::array<glm::vec2,6> textureCoords;
	}
}

#endif