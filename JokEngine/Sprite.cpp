#include "Sprite.h"
namespace Jokengine
{
	Sprite::Sprite(Texture2D *texture,GLint frame,glm::vec2 size)
	:texture(texture),frame(frame),size(size)
	{
	
	}
	Sprite::Sprite(Texture2D *texture)
	:texture(texture),frame(0),size(glm::vec2(texture->width,texture->height))
	{								
	}
}