#include "SpriteSheet.h"
#include <math.h>

SpriteSheet::SpriteSheet(Texture2D* texture,glm::vec2 frameSize)
{
		
	GLint columns=(GLint)floor(texture->Width/frameSize.x);
	GLint rows= (GLint)floor(texture->Height/frameSize.y);
	GLfloat incrementCol= frameSize.x/texture->Width;
	GLfloat incrementRow= frameSize.y/texture->Height;
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
				
			sprites.push_back(Sprite(texture,frameCount,glm::vec2(frameSize.x/texture->Width,frameSize.y/texture->Height)));
			frameCount++;
		}
		
}
