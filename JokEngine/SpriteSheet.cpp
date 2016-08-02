#include "SpriteSheet.h"
#include <math.h>
namespace Jokengine
{
	SpriteSheet::SpriteSheet(Texture2D* texture,glm::vec2 frameSize)
	{
		
		GLint columns=floor(texture->width/frameSize.x);
		GLint rows=floor(texture->height/frameSize.y);
		GLfloat incrementCol=frameSize.x/texture->width;
		GLfloat incrementRow=frameSize.y/texture->height;
		
		for(int i =0;i<rows;i++)
			for(int j=0;j<columns;j++)
			{
				std::array<glm::vec2,6> textCoords;
				textCoord[0]=glm::vec2();
			}
		
	}
}