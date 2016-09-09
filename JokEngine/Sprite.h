#ifndef SPRITE_H
#define SPRITE_H
#include "Texture.h"
#include <glm\matrix.hpp>

class Sprite
{
		public:
			Sprite() {};
			Sprite(Texture2D *texture);
			Sprite(Texture2D *texture, GLint frame, glm::vec2 size);
			Texture2D *texture;
			GLint frame;
			glm::vec2 size;
			GLboolean flipped;
};


#endif