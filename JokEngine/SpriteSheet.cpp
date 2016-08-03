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
		GLint frameCount=0;
		for(int i =0;i<rows;i++)
			for(int j=0;j<columns;j++)
			{
			/*
				std::array<glm::vec2,6> textCoords;
				textCoord[0]=glm::vec2(columns*incrementCol, 1.0f-rows*incrementRow);
				textCoord[1]=glm::vec2(incrementCol+incrementCol*columns, 1.0f-(incrementRow+incrementRow*rows));
				textCoord[2]=glm::vec2(columns*incrementCol, 1.0f-(incrementRow+incrementRow*rows));
				textCoord[3]=glm::vec2(columns*incrementCol, 1.0f-rows*incrementRow);
				textCoord[4]=glm::vec2(incrementCol+incrementCol*columns, 1.0f-rows*incrementRow));
				textCoord[5]=glm::vec2(incrementCol+incrementCol*columns, 1.0f-(incrementRow+incrementRow*rows));
				sprites.push_back(Sprite(texture,textCoords)); */
				
				sprites.push_back(Sprite(texture,frameCount,frameSize));
				frameCount++;
			}
		
	}
}