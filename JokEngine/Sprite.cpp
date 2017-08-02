#include "Sprite.h"

Sprite::Sprite(Texture2D *texture,GLint frame,glm::vec2 size)
:texture(texture),frame(frame),size(size),flipped(true)
{
	
}
Sprite::Sprite(Texture2D *texture)
:texture(texture),frame(0),size(glm::vec2(1,1)), flipped(false)
{								
}
