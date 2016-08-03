#ifndef SPRITE_H
#define SPRITE_H
namespace Jokengine
{
class Sprite
	{
		public:
			Sprite(Texture2D *texture);
			Sprite(Texture2D *texture, glm::vec2 size,GLint frame);
			Texture2D *texture;
			GLint frame;
			glm::vec2 size;
	}
}

#endif