#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#include <vector>
#include "Sprite.h"
namespace Jokengine
{
	class SpriteSheet
	{
		public:
			SpriteSheet() {};
			SpriteSheet(Texture2D* texture,glm::vec2 frameSize);
			std::vector<Sprite> sprites;
	};
}
#endif